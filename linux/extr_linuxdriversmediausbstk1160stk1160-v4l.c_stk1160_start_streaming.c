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
struct TYPE_2__ {int num_bufs; int /*<<< orphan*/ * urb; } ;
struct stk1160 {int /*<<< orphan*/  v4l_lock; int /*<<< orphan*/  udev; scalar_t__ sequence; int /*<<< orphan*/  v4l2_dev; TYPE_1__ isoc_ctl; } ;

/* Variables and functions */
 int ENODEV ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ STK1160_DCTRL ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s_stream ; 
 int stk1160_alloc_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_clear_queue (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_dbg (char*) ; 
 int /*<<< orphan*/  stk1160_err (char*,int,int) ; 
 int stk1160_set_alternate (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_uninit_isoc (struct stk1160*) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,scalar_t__,int) ; 
 int /*<<< orphan*/  usb_set_interface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int stk1160_start_streaming(struct stk1160 *dev)
{
	bool new_pkt_size;
	int rc = 0;
	int i;

	/* Check device presence */
	if (!dev->udev)
		return -ENODEV;

	if (mutex_lock_interruptible(&dev->v4l_lock))
		return -ERESTARTSYS;
	/*
	 * For some reason it is mandatory to set alternate *first*
	 * and only *then* initialize isoc urbs.
	 * Someone please explain me why ;)
	 */
	new_pkt_size = stk1160_set_alternate(dev);

	/*
	 * We (re)allocate isoc urbs if:
	 * there is no allocated isoc urbs, OR
	 * a new dev->max_pkt_size is detected
	 */
	if (!dev->isoc_ctl.num_bufs || new_pkt_size) {
		rc = stk1160_alloc_isoc(dev);
		if (rc < 0)
			goto out_stop_hw;
	}

	/* submit urbs and enables IRQ */
	for (i = 0; i < dev->isoc_ctl.num_bufs; i++) {
		rc = usb_submit_urb(dev->isoc_ctl.urb[i], GFP_KERNEL);
		if (rc) {
			stk1160_err("cannot submit urb[%d] (%d)\n", i, rc);
			goto out_uninit;
		}
	}

	/* Start saa711x */
	v4l2_device_call_all(&dev->v4l2_dev, 0, video, s_stream, 1);

	dev->sequence = 0;

	/* Start stk1160 */
	stk1160_write_reg(dev, STK1160_DCTRL, 0xb3);
	stk1160_write_reg(dev, STK1160_DCTRL+3, 0x00);

	stk1160_dbg("streaming started\n");

	mutex_unlock(&dev->v4l_lock);

	return 0;

out_uninit:
	stk1160_uninit_isoc(dev);
out_stop_hw:
	usb_set_interface(dev->udev, 0, 0);
	stk1160_clear_queue(dev);

	mutex_unlock(&dev->v4l_lock);

	return rc;
}