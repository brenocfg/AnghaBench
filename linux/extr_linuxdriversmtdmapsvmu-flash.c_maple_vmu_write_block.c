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
struct mtd_info {struct mdev_part* priv; } ;
struct memcard {int blocklen; int writecnt; } ;
struct mdev_part {int partition; struct maple_device* mdev; } ;
struct maple_device {int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; TYPE_1__* mq; int /*<<< orphan*/  busy; int /*<<< orphan*/  maple_wait; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  list; int /*<<< orphan*/ * sendbuf; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  MAPLE_COMMAND_BWRITE ; 
 int /*<<< orphan*/  MAPLE_FUNC_MEMCARD ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int maple_add_packet (struct maple_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct memcard* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int maple_vmu_write_block(unsigned int num, const unsigned char *buf,
	struct mtd_info *mtd)
{
	struct memcard *card;
	struct mdev_part *mpart;
	struct maple_device *mdev;
	int partition, error, locking, x, phaselen, wait;
	__be32 *sendbuf;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);

	phaselen = card->blocklen/card->writecnt;

	sendbuf = kmalloc(phaselen + 4, GFP_KERNEL);
	if (!sendbuf) {
		error = -ENOMEM;
		goto fail_nosendbuf;
	}
	for (x = 0; x < card->writecnt; x++) {
		sendbuf[0] = cpu_to_be32(partition << 24 | x << 16 | num);
		memcpy(&sendbuf[1], buf + phaselen * x, phaselen);
		/* wait until the device is not busy doing something else
		* or 1 second - which ever is longer */
		if (atomic_read(&mdev->busy) == 1) {
			wait_event_interruptible_timeout(mdev->maple_wait,
				atomic_read(&mdev->busy) == 0, HZ);
			if (atomic_read(&mdev->busy) == 1) {
				error = -EBUSY;
				dev_notice(&mdev->dev, "VMU write at (%d, %d)"
					"failed - device is busy\n",
					mdev->port, mdev->unit);
				goto fail_nolock;
			}
		}
		atomic_set(&mdev->busy, 1);

		locking = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
			MAPLE_COMMAND_BWRITE, phaselen / 4 + 2, sendbuf);
		wait = wait_event_interruptible_timeout(mdev->maple_wait,
			atomic_read(&mdev->busy) == 0, HZ/10);
		if (locking) {
			error = -EIO;
			atomic_set(&mdev->busy, 0);
			goto fail_nolock;
		}
		if (atomic_read(&mdev->busy) == 2) {
			atomic_set(&mdev->busy, 0);
		} else if (wait == 0 || wait == -ERESTARTSYS) {
			error = -EIO;
			dev_warn(&mdev->dev, "Write at (%d, %d) of block"
				" 0x%X at phase %d failed: could not"
				" communicate with VMU", mdev->port,
				mdev->unit, num, x);
			atomic_set(&mdev->busy, 0);
			kfree(mdev->mq->sendbuf);
			mdev->mq->sendbuf = NULL;
			list_del_init(&(mdev->mq->list));
			goto fail_nolock;
		}
	}
	kfree(sendbuf);

	return card->blocklen;

fail_nolock:
	kfree(sendbuf);
fail_nosendbuf:
	dev_err(&mdev->dev, "VMU (%d, %d): write failed\n", mdev->port,
		mdev->unit);
	return error;
}