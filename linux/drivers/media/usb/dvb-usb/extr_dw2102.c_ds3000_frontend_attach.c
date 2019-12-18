#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct dw2102_state {int /*<<< orphan*/  old_set_voltage; } ;
struct dvb_usb_adapter {TYPE_3__* dev; TYPE_2__* fe_adap; } ;
struct TYPE_6__ {int /*<<< orphan*/  set_voltage; } ;
struct TYPE_9__ {TYPE_1__ ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  udev; int /*<<< orphan*/  i2c_adap; struct dw2102_state* priv; } ;
struct TYPE_7__ {TYPE_4__* fe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW210X_WRITE_MSG ; 
 int EIO ; 
 int /*<<< orphan*/  ds3000_attach ; 
 TYPE_4__* dvb_attach (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  dw210x_op_rw (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  s660_ds3000_config ; 
 int /*<<< orphan*/  s660_set_voltage ; 
 int /*<<< orphan*/  s660_ts2020_config ; 
 int /*<<< orphan*/  ts2020_attach ; 

__attribute__((used)) static int ds3000_frontend_attach(struct dvb_usb_adapter *d)
{
	struct dw2102_state *st = d->dev->priv;
	u8 obuf[] = {7, 1};

	d->fe_adap[0].fe = dvb_attach(ds3000_attach, &s660_ds3000_config,
			&d->dev->i2c_adap);

	if (d->fe_adap[0].fe == NULL)
		return -EIO;

	dvb_attach(ts2020_attach, d->fe_adap[0].fe, &s660_ts2020_config,
		&d->dev->i2c_adap);

	st->old_set_voltage = d->fe_adap[0].fe->ops.set_voltage;
	d->fe_adap[0].fe->ops.set_voltage = s660_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached ds3000+ts2020!");

	return 0;
}