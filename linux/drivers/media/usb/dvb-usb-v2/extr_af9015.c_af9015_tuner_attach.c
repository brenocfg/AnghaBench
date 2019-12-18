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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {struct usb_interface* intf; } ;
struct dvb_usb_adapter {size_t id; TYPE_4__** fe; } ;
struct af9015_state {scalar_t__* tuner_sleep; scalar_t__* tuner_init; TYPE_1__* af9013_pdata; int /*<<< orphan*/ * mt2060_if1; struct i2c_client** demod_i2c_client; } ;
struct TYPE_6__ {scalar_t__ sleep; scalar_t__ init; } ;
struct TYPE_7__ {TYPE_2__ tuner_ops; } ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct TYPE_5__ {int tuner; struct i2c_adapter* (* get_i2c_adapter ) (struct i2c_client*) ;} ;

/* Variables and functions */
#define  AF9013_TUNER_ENV77H11D5 140 
#define  AF9013_TUNER_MC44S803 139 
#define  AF9013_TUNER_MT2060 138 
#define  AF9013_TUNER_MT2060_2 137 
#define  AF9013_TUNER_MXL5003D 136 
#define  AF9013_TUNER_MXL5005D 135 
#define  AF9013_TUNER_MXL5005R 134 
#define  AF9013_TUNER_MXL5007T 133 
#define  AF9013_TUNER_QT1010 132 
#define  AF9013_TUNER_QT1010A 131 
#define  AF9013_TUNER_TDA18218 130 
#define  AF9013_TUNER_TDA18271 129 
#define  AF9013_TUNER_UNKNOWN 128 
 int /*<<< orphan*/  DVB_PLL_TDA665X ; 
 int ENODEV ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 int /*<<< orphan*/  af9015_mc44s803_config ; 
 int /*<<< orphan*/  af9015_mt2060_config ; 
 int /*<<< orphan*/  af9015_mxl5003_config ; 
 int /*<<< orphan*/  af9015_mxl5005_config ; 
 int /*<<< orphan*/  af9015_mxl5007t_config ; 
 int /*<<< orphan*/  af9015_qt1010_config ; 
 int /*<<< orphan*/  af9015_tda18218_config ; 
 int /*<<< orphan*/  af9015_tda18271_config ; 
 scalar_t__ af9015_tuner_init ; 
 scalar_t__ af9015_tuner_sleep ; 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * dvb_attach (int /*<<< orphan*/ ,TYPE_4__*,int,int,...) ; 
 int /*<<< orphan*/  dvb_pll_attach ; 
 int /*<<< orphan*/  mc44s803_attach ; 
 int /*<<< orphan*/  mt2060_attach ; 
 int /*<<< orphan*/  mxl5005s_attach ; 
 int /*<<< orphan*/  mxl5007t_attach ; 
 int /*<<< orphan*/  qt1010_attach ; 
 struct i2c_adapter* stub1 (struct i2c_client*) ; 
 int /*<<< orphan*/  tda18218_attach ; 
 int /*<<< orphan*/  tda18271_attach ; 

__attribute__((used)) static int af9015_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct dvb_usb_device *d = adap_to_d(adap);
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	struct i2c_client *client;
	struct i2c_adapter *adapter;
	int ret;

	dev_dbg(&intf->dev, "adap id %u\n", adap->id);

	client = state->demod_i2c_client[adap->id];
	adapter = state->af9013_pdata[adap->id].get_i2c_adapter(client);

	switch (state->af9013_pdata[adap->id].tuner) {
	case AF9013_TUNER_MT2060:
	case AF9013_TUNER_MT2060_2:
		ret = dvb_attach(mt2060_attach, adap->fe[0], adapter,
				 &af9015_mt2060_config,
				 state->mt2060_if1[adap->id]) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_QT1010:
	case AF9013_TUNER_QT1010A:
		ret = dvb_attach(qt1010_attach, adap->fe[0], adapter,
				 &af9015_qt1010_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_TDA18271:
		ret = dvb_attach(tda18271_attach, adap->fe[0], 0x60, adapter,
				 &af9015_tda18271_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_TDA18218:
		ret = dvb_attach(tda18218_attach, adap->fe[0], adapter,
				 &af9015_tda18218_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_MXL5003D:
		ret = dvb_attach(mxl5005s_attach, adap->fe[0], adapter,
				 &af9015_mxl5003_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_MXL5005D:
	case AF9013_TUNER_MXL5005R:
		ret = dvb_attach(mxl5005s_attach, adap->fe[0], adapter,
				 &af9015_mxl5005_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_ENV77H11D5:
		ret = dvb_attach(dvb_pll_attach, adap->fe[0], 0x60, adapter,
				 DVB_PLL_TDA665X) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_MC44S803:
		ret = dvb_attach(mc44s803_attach, adap->fe[0], adapter,
				 &af9015_mc44s803_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_MXL5007T:
		ret = dvb_attach(mxl5007t_attach, adap->fe[0], adapter,
				 0x60, &af9015_mxl5007t_config) == NULL ? -ENODEV : 0;
		break;
	case AF9013_TUNER_UNKNOWN:
	default:
		dev_err(&intf->dev, "unknown tuner, tuner id %02x\n",
			state->af9013_pdata[adap->id].tuner);
		ret = -ENODEV;
	}

	if (adap->fe[0]->ops.tuner_ops.init) {
		state->tuner_init[adap->id] =
			adap->fe[0]->ops.tuner_ops.init;
		adap->fe[0]->ops.tuner_ops.init = af9015_tuner_init;
	}

	if (adap->fe[0]->ops.tuner_ops.sleep) {
		state->tuner_sleep[adap->id] =
			adap->fe[0]->ops.tuner_ops.sleep;
		adap->fe[0]->ops.tuner_ops.sleep = af9015_tuner_sleep;
	}

	return ret;
}