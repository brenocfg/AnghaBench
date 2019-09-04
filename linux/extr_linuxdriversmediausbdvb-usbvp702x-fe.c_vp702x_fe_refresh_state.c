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
typedef  void* u8 ;
struct vp702x_fe_state {int status_check_interval; scalar_t__ next_status_check; void* sig; TYPE_1__* d; void* snr; void* lock; } ;
struct vp702x_device_state {void** buf; int /*<<< orphan*/  buf_mutex; } ;
struct TYPE_2__ {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  READ_STATUS ; 
 int /*<<< orphan*/  READ_TUNER_REG_REQ ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vp702x_usb_in_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void**,int) ; 

__attribute__((used)) static int vp702x_fe_refresh_state(struct vp702x_fe_state *st)
{
	struct vp702x_device_state *dst = st->d->priv;
	u8 *buf;

	if (time_after(jiffies, st->next_status_check)) {
		mutex_lock(&dst->buf_mutex);
		buf = dst->buf;

		vp702x_usb_in_op(st->d, READ_STATUS, 0, 0, buf, 10);
		st->lock = buf[4];

		vp702x_usb_in_op(st->d, READ_TUNER_REG_REQ, 0x11, 0, buf, 1);
		st->snr = buf[0];

		vp702x_usb_in_op(st->d, READ_TUNER_REG_REQ, 0x15, 0, buf, 1);
		st->sig = buf[0];

		mutex_unlock(&dst->buf_mutex);
		st->next_status_check = jiffies + (st->status_check_interval*HZ)/1000;
	}
	return 0;
}