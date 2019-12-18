#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct vmupart {int dummy; } ;
struct mtd_info {int dummy; } ;
struct memcard {unsigned long partitions; unsigned long blocklen; unsigned long writecnt; unsigned long readcnt; unsigned long removeable; struct memcard* parts; struct memcard* mtd; scalar_t__ partition; } ;
struct TYPE_2__ {int /*<<< orphan*/ * function_data; int /*<<< orphan*/  function; } ;
struct maple_device {int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; int /*<<< orphan*/  busy; int /*<<< orphan*/  maple_wait; TYPE_1__ devinfo; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  MAPLE_COMMAND_GETMINFO ; 
 int /*<<< orphan*/  MAPLE_FUNC_MEMCARD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned long be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hweight_long (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct memcard*) ; 
 struct memcard* kmalloc (int,int /*<<< orphan*/ ) ; 
 void* kmalloc_array (unsigned long,int,int /*<<< orphan*/ ) ; 
 int maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maple_getcond_callback (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maple_set_drvdata (struct maple_device*,struct memcard*) ; 
 int /*<<< orphan*/  vmu_queryblocks ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vmu_connect(struct maple_device *mdev)
{
	unsigned long test_flash_data, basic_flash_data;
	int c, error;
	struct memcard *card;
	u32 partnum = 0;

	test_flash_data = be32_to_cpu(mdev->devinfo.function);
	/* Need to count how many bits are set - to find out which
	 * function_data element has details of the memory card
	 */
	c = hweight_long(test_flash_data);

	basic_flash_data = be32_to_cpu(mdev->devinfo.function_data[c - 1]);

	card = kmalloc(sizeof(struct memcard), GFP_KERNEL);
	if (!card) {
		error = -ENOMEM;
		goto fail_nomem;
	}

	card->partitions = (basic_flash_data >> 24 & 0xFF) + 1;
	card->blocklen = ((basic_flash_data >> 16 & 0xFF) + 1) << 5;
	card->writecnt = basic_flash_data >> 12 & 0xF;
	card->readcnt = basic_flash_data >> 8 & 0xF;
	card->removeable = basic_flash_data >> 7 & 1;

	card->partition = 0;

	/*
	* Not sure there are actually any multi-partition devices in the
	* real world, but the hardware supports them, so, so will we
	*/
	card->parts = kmalloc_array(card->partitions, sizeof(struct vmupart),
				    GFP_KERNEL);
	if (!card->parts) {
		error = -ENOMEM;
		goto fail_partitions;
	}

	card->mtd = kmalloc_array(card->partitions, sizeof(struct mtd_info),
				  GFP_KERNEL);
	if (!card->mtd) {
		error = -ENOMEM;
		goto fail_mtd_info;
	}

	maple_set_drvdata(mdev, card);

	/*
	* We want to trap meminfo not get cond
	* so set interval to zero, but rely on maple bus
	* driver to pass back the results of the meminfo
	*/
	maple_getcond_callback(mdev, vmu_queryblocks, 0,
		MAPLE_FUNC_MEMCARD);

	/* Make sure we are clear to go */
	if (atomic_read(&mdev->busy) == 1) {
		wait_event_interruptible_timeout(mdev->maple_wait,
			atomic_read(&mdev->busy) == 0, HZ);
		if (atomic_read(&mdev->busy) == 1) {
			dev_notice(&mdev->dev, "VMU at (%d, %d) is busy\n",
				mdev->port, mdev->unit);
			error = -EAGAIN;
			goto fail_device_busy;
		}
	}

	atomic_set(&mdev->busy, 1);

	/*
	* Set up the minfo call: vmu_queryblocks will handle
	* the information passed back
	*/
	error = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
		MAPLE_COMMAND_GETMINFO, 2, &partnum);
	if (error) {
		dev_err(&mdev->dev, "Could not lock VMU at (%d, %d)"
			" error is 0x%X\n", mdev->port, mdev->unit, error);
		goto fail_mtd_info;
	}
	return 0;

fail_device_busy:
	kfree(card->mtd);
fail_mtd_info:
	kfree(card->parts);
fail_partitions:
	kfree(card);
fail_nomem:
	return error;
}