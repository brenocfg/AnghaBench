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
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; struct dtt200u_state* priv; } ;
struct dvb_usb_adapter {struct dvb_usb_device* dev; } ;
struct dtt200u_state {int* data; } ;

/* Variables and functions */
 int SET_PID_FILTER ; 
 int dvb_usb_generic_write (struct dvb_usb_device*,int*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_pid_filter(struct dvb_usb_adapter *adap, int index, u16 pid, int onoff)
{
	struct dvb_usb_device *d = adap->dev;
	struct dtt200u_state *st = d->priv;
	int ret;

	pid = onoff ? pid : 0;

	mutex_lock(&d->data_mutex);
	st->data[0] = SET_PID_FILTER;
	st->data[1] = index;
	st->data[2] = pid & 0xff;
	st->data[3] = (pid >> 8) & 0x1f;

	ret = dvb_usb_generic_write(adap->dev, st->data, 4);
	mutex_unlock(&d->data_mutex);

	return ret;
}