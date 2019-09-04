#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {TYPE_2__* fe_adap; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dw3101_tda10023_config ; 
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  tda10023_attach ; 

__attribute__((used)) static int dw3101_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe_adap[0].fe = dvb_attach(tda10023_attach, &dw3101_tda10023_config,
				&d->dev->i2c_adap, 0x48);
	if (d->fe_adap[0].fe != NULL) {
		info("Attached tda10023!");
		return 0;
	}
	return -EIO;
}