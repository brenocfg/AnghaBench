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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int /*<<< orphan*/  udev; struct az6007_device_state* priv; } ;
struct az6007_device_state {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int __az6007_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int az6007_write(struct dvb_usb_device *d, u8 req, u16 value,
			    u16 index, u8 *b, int blen)
{
	struct az6007_device_state *st = d->priv;
	int ret;

	if (mutex_lock_interruptible(&st->mutex) < 0)
		return -EAGAIN;

	ret = __az6007_write(d->udev, req, value, index, b, blen);

	mutex_unlock(&st->mutex);

	return ret;
}