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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct dib0700_state* priv; } ;
struct dib0700_state {int fw_use_new_i2c_api; } ;

/* Variables and functions */
 int dib0700_i2c_xfer_legacy (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int dib0700_i2c_xfer_new (struct i2c_adapter*,struct i2c_msg*,int) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int dib0700_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msg,
			    int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct dib0700_state *st = d->priv;

	if (st->fw_use_new_i2c_api == 1) {
		/* User running at least fw 1.20 */
		return dib0700_i2c_xfer_new(adap, msg, num);
	} else {
		/* Use legacy calls */
		return dib0700_i2c_xfer_legacy(adap, msg, num);
	}
}