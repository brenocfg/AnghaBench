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
struct TYPE_4__ {scalar_t__ fe; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  cxusb_aver_lgdt3303_config ; 
 scalar_t__ dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lgdt330x_attach ; 

__attribute__((used)) static int cxusb_aver_lgdt3303_frontend_attach(struct dvb_usb_adapter *adap)
{
	adap->fe_adap[0].fe = dvb_attach(lgdt330x_attach,
					 &cxusb_aver_lgdt3303_config,
					 0x0e,
					 &adap->dev->i2c_adap);
	if (adap->fe_adap[0].fe)
		return 0;

	return -EIO;
}