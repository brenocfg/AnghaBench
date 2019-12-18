#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fw_info {int /*<<< orphan*/  suballocator_size; int /*<<< orphan*/  mailbox_size; int /*<<< orphan*/  mailbox_status; int /*<<< orphan*/  mailbox_cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; } ;
struct allegro_dev {TYPE_1__ suballocator; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  mbox_status; int /*<<< orphan*/  mbox_command; } ;

/* Variables and functions */
 int EIO ; 
 int allegro_alloc_buffer (struct allegro_dev*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allegro_free_buffer (struct allegro_dev*,TYPE_1__*) ; 
 int /*<<< orphan*/  allegro_mbox_init (struct allegro_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allegro_mcu_disable_interrupts (struct allegro_dev*) ; 
 int /*<<< orphan*/  allegro_mcu_enable_interrupts (struct allegro_dev*) ; 
 int /*<<< orphan*/  allegro_mcu_reset (struct allegro_dev*) ; 
 int /*<<< orphan*/  allegro_mcu_send_init (struct allegro_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allegro_mcu_start (struct allegro_dev*) ; 
 int allegro_mcu_wait_for_init_timeout (struct allegro_dev*,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int allegro_mcu_hw_init(struct allegro_dev *dev,
			       const struct fw_info *info)
{
	int err;

	allegro_mbox_init(dev, &dev->mbox_command,
			  info->mailbox_cmd, info->mailbox_size);
	allegro_mbox_init(dev, &dev->mbox_status,
			  info->mailbox_status, info->mailbox_size);

	allegro_mcu_enable_interrupts(dev);

	/* The mcu sends INIT after reset. */
	allegro_mcu_start(dev);
	err = allegro_mcu_wait_for_init_timeout(dev, 5000);
	if (err < 0) {
		v4l2_err(&dev->v4l2_dev,
			 "mcu did not send INIT after reset\n");
		err = -EIO;
		goto err_disable_interrupts;
	}

	err = allegro_alloc_buffer(dev, &dev->suballocator,
				   info->suballocator_size);
	if (err) {
		v4l2_err(&dev->v4l2_dev,
			 "failed to allocate %zu bytes for suballocator\n",
			 info->suballocator_size);
		goto err_reset_mcu;
	}

	allegro_mcu_send_init(dev, dev->suballocator.paddr,
			      dev->suballocator.size);
	err = allegro_mcu_wait_for_init_timeout(dev, 5000);
	if (err < 0) {
		v4l2_err(&dev->v4l2_dev,
			 "mcu failed to configure sub-allocator\n");
		err = -EIO;
		goto err_free_suballocator;
	}

	return 0;

err_free_suballocator:
	allegro_free_buffer(dev, &dev->suballocator);
err_reset_mcu:
	allegro_mcu_reset(dev);
err_disable_interrupts:
	allegro_mcu_disable_interrupts(dev);

	return err;
}