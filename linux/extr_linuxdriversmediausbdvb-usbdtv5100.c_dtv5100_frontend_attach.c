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
struct dvb_usb_adapter {TYPE_2__* fe_adap; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/ * i2c_gate_ctrl; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_6__ {TYPE_4__* fe; } ;
struct TYPE_5__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dtv5100_zl10353_config ; 
 TYPE_4__* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zl10353_attach ; 

__attribute__((used)) static int dtv5100_frontend_attach(struct dvb_usb_adapter *adap)
{
	adap->fe_adap[0].fe = dvb_attach(zl10353_attach, &dtv5100_zl10353_config,
			      &adap->dev->i2c_adap);
	if (adap->fe_adap[0].fe == NULL)
		return -EIO;

	/* disable i2c gate, or it won't work... is this safe? */
	adap->fe_adap[0].fe->ops.i2c_gate_ctrl = NULL;

	return 0;
}