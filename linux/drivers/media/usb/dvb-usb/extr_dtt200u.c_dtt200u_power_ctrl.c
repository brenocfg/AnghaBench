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
struct dvb_usb_device {int /*<<< orphan*/  data_mutex; struct dtt200u_state* priv; } ;
struct dtt200u_state {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_INIT ; 
 int dvb_usb_generic_write (struct dvb_usb_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dtt200u_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	struct dtt200u_state *st = d->priv;
	int ret = 0;

	mutex_lock(&d->data_mutex);

	st->data[0] = SET_INIT;

	if (onoff)
		ret = dvb_usb_generic_write(d, st->data, 2);

	mutex_unlock(&d->data_mutex);
	return ret;
}