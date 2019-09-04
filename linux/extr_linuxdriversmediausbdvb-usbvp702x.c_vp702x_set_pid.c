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
typedef  int u8 ;
typedef  int u16 ;
struct vp702x_device_state {int* buf; int /*<<< orphan*/  buf_mutex; } ;
struct vp702x_adapter_state {int pid_filter_state; } ;
struct dvb_usb_adapter {TYPE_1__* dev; struct vp702x_adapter_state* priv; } ;
typedef  int pid ;
struct TYPE_2__ {struct vp702x_device_state* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vp702x_set_pld_state (struct dvb_usb_adapter*,int) ; 
 int /*<<< orphan*/  vp702x_usb_in_op (TYPE_1__*,int,int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vp702x_set_pid(struct dvb_usb_adapter *adap, u16 pid, u8 id, int onoff)
{
	struct vp702x_adapter_state *st = adap->priv;
	struct vp702x_device_state *dst = adap->dev->priv;
	u8 *buf;

	if (onoff)
		st->pid_filter_state |=  (1 << id);
	else {
		st->pid_filter_state &= ~(1 << id);
		pid = 0xffff;
	}

	id = 0x10 + id*2;

	vp702x_set_pld_state(adap, st->pid_filter_state);

	mutex_lock(&dst->buf_mutex);

	buf = dst->buf;
	memset(buf, 0, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid >> 8) & 0xff) << 8) | (id), 0, buf, 16);
	vp702x_usb_in_op(adap->dev, 0xe0, (((pid     ) & 0xff) << 8) | (id+1), 0, buf, 16);

	mutex_unlock(&dst->buf_mutex);

	return 0;
}