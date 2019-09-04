#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rtl28xxu_dev {int tuner; int /*<<< orphan*/  demod_i2c_adapter; } ;
struct dvb_usb_device {TYPE_1__* intf; } ;
struct dvb_usb_adapter {int /*<<< orphan*/ * fe; } ;
struct dvb_frontend {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
#define  TUNER_RTL2830_MT2060 130 
#define  TUNER_RTL2830_MXL5005S 129 
#define  TUNER_RTL2830_QT1010 128 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct rtl28xxu_dev* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  mt2060_attach ; 
 int /*<<< orphan*/  mxl5005s_attach ; 
 int /*<<< orphan*/  qt1010_attach ; 
 int /*<<< orphan*/  rtl28xxu_mt2060_config ; 
 int /*<<< orphan*/  rtl28xxu_mxl5005s_config ; 
 int /*<<< orphan*/  rtl28xxu_qt1010_config ; 

__attribute__((used)) static int rtl2831u_tuner_attach(struct dvb_usb_adapter *adap)
{
	int ret;
	struct dvb_usb_device *d = adap_to_d(adap);
	struct rtl28xxu_dev *dev = d_to_priv(d);
	struct dvb_frontend *fe;

	dev_dbg(&d->intf->dev, "\n");

	switch (dev->tuner) {
	case TUNER_RTL2830_QT1010:
		fe = dvb_attach(qt1010_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_qt1010_config);
		break;
	case TUNER_RTL2830_MT2060:
		fe = dvb_attach(mt2060_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_mt2060_config, 1220);
		break;
	case TUNER_RTL2830_MXL5005S:
		fe = dvb_attach(mxl5005s_attach, adap->fe[0],
				dev->demod_i2c_adapter,
				&rtl28xxu_mxl5005s_config);
		break;
	default:
		fe = NULL;
		dev_err(&d->intf->dev, "unknown tuner %d\n", dev->tuner);
	}

	if (fe == NULL) {
		ret = -ENODEV;
		goto err;
	}

	return 0;
err:
	dev_dbg(&d->intf->dev, "failed=%d\n", ret);
	return ret;
}