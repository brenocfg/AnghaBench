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
struct i2c_adapter {int dummy; } ;
struct dvb_usb_adapter {size_t id; TYPE_4__* fe_adap; TYPE_3__* dev; } ;
typedef  int s8 ;
struct TYPE_8__ {int /*<<< orphan*/  fe; } ;
struct TYPE_7__ {TYPE_2__* udev; struct i2c_adapter i2c_adap; } ;
struct TYPE_5__ {scalar_t__ idVendor; scalar_t__ idProduct; } ;
struct TYPE_6__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_PID_HAUPPAUGE_NOVA_T_500_2 ; 
 int /*<<< orphan*/  USB_VID_HAUPPAUGE ; 
 int /*<<< orphan*/ * bristol_mt2060_config ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct i2c_adapter* dib3000mc_get_tuner_i2c_master (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct i2c_adapter*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eeprom_read (struct i2c_adapter*,size_t,int*) ; 
 int /*<<< orphan*/  mt2060_attach ; 

__attribute__((used)) static int bristol_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct i2c_adapter *prim_i2c = &adap->dev->i2c_adap;
	struct i2c_adapter *tun_i2c = dib3000mc_get_tuner_i2c_master(adap->fe_adap[0].fe, 1);
	s8 a;
	int if1=1220;
	if (adap->dev->udev->descriptor.idVendor  == cpu_to_le16(USB_VID_HAUPPAUGE) &&
		adap->dev->udev->descriptor.idProduct == cpu_to_le16(USB_PID_HAUPPAUGE_NOVA_T_500_2)) {
		if (!eeprom_read(prim_i2c,0x59 + adap->id,&a)) if1=1220+a;
	}
	return dvb_attach(mt2060_attach, adap->fe_adap[0].fe, tun_i2c,
			  &bristol_mt2060_config[adap->id], if1) == NULL ?
			  -ENODEV : 0;
}