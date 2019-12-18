#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_3__* fe_adap; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  set_voltage; } ;
struct TYPE_8__ {TYPE_1__ ops; } ;
struct TYPE_7__ {TYPE_4__* fe; } ;
struct TYPE_6__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_4__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  opera1_set_voltage ; 
 int /*<<< orphan*/  opera1_stv0299_config ; 
 int /*<<< orphan*/  stv0299_attach ; 

__attribute__((used)) static int opera1_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe_adap[0].fe = dvb_attach(stv0299_attach, &opera1_stv0299_config,
				      &d->dev->i2c_adap);
	if ((d->fe_adap[0].fe) != NULL) {
		d->fe_adap[0].fe->ops.set_voltage = opera1_set_voltage;
		return 0;
	}
	info("not attached stv0299");
	return -EIO;
}