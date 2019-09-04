#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int /*<<< orphan*/  usb_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  REQUEST_IN ; 
 int /*<<< orphan*/  REQUEST_OUT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vp702x_usb_in_op_unlocked (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int vp702x_usb_out_op_unlocked (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int vp702x_usb_inout_op(struct dvb_usb_device *d, u8 *o, int olen, u8 *i, int ilen, int msec)
{
	int ret;

	if ((ret = mutex_lock_interruptible(&d->usb_mutex)))
		return ret;

	ret = vp702x_usb_out_op_unlocked(d, REQUEST_OUT, 0, 0, o, olen);
	msleep(msec);
	ret = vp702x_usb_in_op_unlocked(d, REQUEST_IN, 0, 0, i, ilen);

	mutex_unlock(&d->usb_mutex);
	return ret;
}