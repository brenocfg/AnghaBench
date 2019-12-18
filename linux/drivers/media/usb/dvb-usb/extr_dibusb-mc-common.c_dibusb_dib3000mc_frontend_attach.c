#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dvb_usb_adapter {struct dibusb_state* priv; TYPE_4__* fe_adap; TYPE_3__* dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  pid_ctrl; int /*<<< orphan*/  pid_parse; } ;
struct dibusb_state {TYPE_5__ ops; } ;
struct TYPE_9__ {int /*<<< orphan*/ * fe; } ;
struct TYPE_8__ {int /*<<< orphan*/  i2c_adap; TYPE_2__* udev; } ;
struct TYPE_6__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_7__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_DIB3000MC_I2C_ADDRESS ; 
 int /*<<< orphan*/  DEFAULT_DIB3000P_I2C_ADDRESS ; 
 int ENODEV ; 
 scalar_t__ USB_PID_LITEON_DVB_T_WARM ; 
 scalar_t__ USB_VID_LITEON ; 
 int /*<<< orphan*/  dib3000mc_attach ; 
 int /*<<< orphan*/  dib3000mc_pid_control ; 
 int /*<<< orphan*/  dib3000mc_pid_parse ; 
 void* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod3000p_dib3000p_config ; 
 int /*<<< orphan*/  msleep (int) ; 

int dibusb_dib3000mc_frontend_attach(struct dvb_usb_adapter *adap)
{
	if (le16_to_cpu(adap->dev->udev->descriptor.idVendor) == USB_VID_LITEON &&
	    le16_to_cpu(adap->dev->udev->descriptor.idProduct) ==
			USB_PID_LITEON_DVB_T_WARM) {
		msleep(1000);
	}

	adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
					 &adap->dev->i2c_adap,
					 DEFAULT_DIB3000P_I2C_ADDRESS,
					 &mod3000p_dib3000p_config);
	if ((adap->fe_adap[0].fe) == NULL)
		adap->fe_adap[0].fe = dvb_attach(dib3000mc_attach,
						 &adap->dev->i2c_adap,
						 DEFAULT_DIB3000MC_I2C_ADDRESS,
						 &mod3000p_dib3000p_config);
	if ((adap->fe_adap[0].fe) != NULL) {
		if (adap->priv != NULL) {
			struct dibusb_state *st = adap->priv;
			st->ops.pid_parse = dib3000mc_pid_parse;
			st->ops.pid_ctrl  = dib3000mc_pid_control;
		}
		return 0;
	}
	return -ENODEV;
}