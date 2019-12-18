#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct tua9001_platform_data {struct dvb_frontend* dvb_frontend; } ;
struct state {struct platform_device** platform_device_tuner; int /*<<< orphan*/  dual_mode; TYPE_3__* af9033_config; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct platform_device {TYPE_2__ dev; } ;
struct it913x_platform_data {int /*<<< orphan*/  role; struct dvb_frontend* fe; int /*<<< orphan*/  regmap; } ;
struct i2c_msg {int addr; int len; char* buf; int /*<<< orphan*/  flags; } ;
struct fc2580_platform_data {struct dvb_frontend* dvb_frontend; } ;
struct dvb_usb_device {struct usb_interface* intf; int /*<<< orphan*/  i2c_adap; } ;
struct dvb_usb_adapter {int id; struct dvb_frontend** fe; } ;
struct dvb_frontend {int dummy; } ;
typedef  int /*<<< orphan*/  it913x_pdata ;
struct TYPE_6__ {int tuner; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
#define  AF9033_TUNER_FC0011 139 
#define  AF9033_TUNER_FC0012 138 
#define  AF9033_TUNER_FC2580 137 
#define  AF9033_TUNER_IT9135_38 136 
#define  AF9033_TUNER_IT9135_51 135 
#define  AF9033_TUNER_IT9135_52 134 
#define  AF9033_TUNER_IT9135_60 133 
#define  AF9033_TUNER_IT9135_61 132 
#define  AF9033_TUNER_IT9135_62 131 
#define  AF9033_TUNER_MXL5007T 130 
#define  AF9033_TUNER_TDA18218 129 
#define  AF9033_TUNER_TUA9001 128 
 int ENODEV ; 
 int /*<<< orphan*/  IS_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  IT913X_ROLE_DUAL_MASTER ; 
 int /*<<< orphan*/  IT913X_ROLE_DUAL_SLAVE ; 
 int /*<<< orphan*/  IT913X_ROLE_SINGLE ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 struct dvb_usb_device* adap_to_d (struct dvb_usb_adapter*) ; 
 struct state* adap_to_priv (struct dvb_usb_adapter*) ; 
 int af9035_add_i2c_dev (struct dvb_usb_device*,char*,int,struct tua9001_platform_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  af9035_fc0011_config ; 
 int /*<<< orphan*/ * af9035_fc0012_config ; 
 int /*<<< orphan*/ * af9035_mxl5007t_config ; 
 int /*<<< orphan*/  af9035_tda18218_config ; 
 int af9035_wr_reg (struct dvb_usb_device*,int,int) ; 
 int af9035_wr_reg_mask (struct dvb_usb_device*,int,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 struct dvb_frontend* dvb_attach (int /*<<< orphan*/ ,struct dvb_frontend*,int /*<<< orphan*/ *,int,...) ; 
 int /*<<< orphan*/  fc0011_attach ; 
 int /*<<< orphan*/  fc0012_attach ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mxl5007t_attach ; 
 struct platform_device* platform_device_register_data (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,struct it913x_platform_data*,int) ; 
 int /*<<< orphan*/  platform_device_unregister (struct platform_device*) ; 
 int /*<<< orphan*/  request_module (char*,char*) ; 
 int /*<<< orphan*/  tda18218_attach ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int af9035_tuner_attach(struct dvb_usb_adapter *adap)
{
	struct state *state = adap_to_priv(adap);
	struct dvb_usb_device *d = adap_to_d(adap);
	struct usb_interface *intf = d->intf;
	int ret;
	struct dvb_frontend *fe;
	struct i2c_msg msg[1];
	u8 tuner_addr;

	dev_dbg(&intf->dev, "adap->id=%d\n", adap->id);

	/*
	 * XXX: Hack used in that function: we abuse unused I2C address bit [7]
	 * to carry info about used I2C bus for dual tuner configuration.
	 */

	switch (state->af9033_config[adap->id].tuner) {
	case AF9033_TUNER_TUA9001: {
		struct tua9001_platform_data tua9001_pdata = {
			.dvb_frontend = adap->fe[0],
		};

		/*
		 * AF9035 gpiot3 = TUA9001 RESETN
		 * AF9035 gpiot2 = TUA9001 RXEN
		 */

		/* configure gpiot2 and gpiot2 as output */
		ret = af9035_wr_reg_mask(d, 0x00d8ec, 0x01, 0x01);
		if (ret < 0)
			goto err;

		ret = af9035_wr_reg_mask(d, 0x00d8ed, 0x01, 0x01);
		if (ret < 0)
			goto err;

		ret = af9035_wr_reg_mask(d, 0x00d8e8, 0x01, 0x01);
		if (ret < 0)
			goto err;

		ret = af9035_wr_reg_mask(d, 0x00d8e9, 0x01, 0x01);
		if (ret < 0)
			goto err;

		/* attach tuner */
		ret = af9035_add_i2c_dev(d, "tua9001", 0x60, &tua9001_pdata,
					 &d->i2c_adap);
		if (ret)
			goto err;

		fe = adap->fe[0];
		break;
	}
	case AF9033_TUNER_FC0011:
		fe = dvb_attach(fc0011_attach, adap->fe[0],
				&d->i2c_adap, &af9035_fc0011_config);
		break;
	case AF9033_TUNER_MXL5007T:
		if (adap->id == 0) {
			ret = af9035_wr_reg(d, 0x00d8e0, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8e1, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8df, 0);
			if (ret < 0)
				goto err;

			msleep(30);

			ret = af9035_wr_reg(d, 0x00d8df, 1);
			if (ret < 0)
				goto err;

			msleep(300);

			ret = af9035_wr_reg(d, 0x00d8c0, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8c1, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8bf, 0);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8b4, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8b5, 1);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg(d, 0x00d8b3, 1);
			if (ret < 0)
				goto err;

			tuner_addr = 0x60;
		} else {
			tuner_addr = 0x60 | 0x80; /* I2C bus hack */
		}

		/* attach tuner */
		fe = dvb_attach(mxl5007t_attach, adap->fe[0], &d->i2c_adap,
				tuner_addr, &af9035_mxl5007t_config[adap->id]);
		break;
	case AF9033_TUNER_TDA18218:
		/* attach tuner */
		fe = dvb_attach(tda18218_attach, adap->fe[0],
				&d->i2c_adap, &af9035_tda18218_config);
		break;
	case AF9033_TUNER_FC2580: {
		struct fc2580_platform_data fc2580_pdata = {
			.dvb_frontend = adap->fe[0],
		};

		/* Tuner enable using gpiot2_o, gpiot2_en and gpiot2_on  */
		ret = af9035_wr_reg_mask(d, 0xd8eb, 0x01, 0x01);
		if (ret < 0)
			goto err;

		ret = af9035_wr_reg_mask(d, 0xd8ec, 0x01, 0x01);
		if (ret < 0)
			goto err;

		ret = af9035_wr_reg_mask(d, 0xd8ed, 0x01, 0x01);
		if (ret < 0)
			goto err;

		usleep_range(10000, 50000);
		/* attach tuner */
		ret = af9035_add_i2c_dev(d, "fc2580", 0x56, &fc2580_pdata,
					 &d->i2c_adap);
		if (ret)
			goto err;

		fe = adap->fe[0];
		break;
	}
	case AF9033_TUNER_FC0012:
		/*
		 * AF9035 gpiot2 = FC0012 enable
		 * XXX: there seems to be something on gpioh8 too, but on my
		 * my test I didn't find any difference.
		 */

		if (adap->id == 0) {
			/* configure gpiot2 as output and high */
			ret = af9035_wr_reg_mask(d, 0xd8eb, 0x01, 0x01);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg_mask(d, 0xd8ec, 0x01, 0x01);
			if (ret < 0)
				goto err;

			ret = af9035_wr_reg_mask(d, 0xd8ed, 0x01, 0x01);
			if (ret < 0)
				goto err;
		} else {
			/*
			 * FIXME: That belongs for the FC0012 driver.
			 * Write 02 to FC0012 master tuner register 0d directly
			 * in order to make slave tuner working.
			 */
			msg[0].addr = 0x63;
			msg[0].flags = 0;
			msg[0].len = 2;
			msg[0].buf = "\x0d\x02";
			ret = i2c_transfer(&d->i2c_adap, msg, 1);
			if (ret < 0)
				goto err;
		}

		usleep_range(10000, 50000);

		fe = dvb_attach(fc0012_attach, adap->fe[0], &d->i2c_adap,
				&af9035_fc0012_config[adap->id]);
		break;
	case AF9033_TUNER_IT9135_38:
	case AF9033_TUNER_IT9135_51:
	case AF9033_TUNER_IT9135_52:
	case AF9033_TUNER_IT9135_60:
	case AF9033_TUNER_IT9135_61:
	case AF9033_TUNER_IT9135_62:
	{
		struct platform_device *pdev;
		const char *name;
		struct it913x_platform_data it913x_pdata = {
			.regmap = state->af9033_config[adap->id].regmap,
			.fe = adap->fe[0],
		};

		switch (state->af9033_config[adap->id].tuner) {
		case AF9033_TUNER_IT9135_38:
		case AF9033_TUNER_IT9135_51:
		case AF9033_TUNER_IT9135_52:
			name = "it9133ax-tuner";
			break;
		case AF9033_TUNER_IT9135_60:
		case AF9033_TUNER_IT9135_61:
		case AF9033_TUNER_IT9135_62:
			name = "it9133bx-tuner";
			break;
		default:
			ret = -ENODEV;
			goto err;
		}

		if (state->dual_mode) {
			if (adap->id == 0)
				it913x_pdata.role = IT913X_ROLE_DUAL_MASTER;
			else
				it913x_pdata.role = IT913X_ROLE_DUAL_SLAVE;
		} else {
			it913x_pdata.role = IT913X_ROLE_SINGLE;
		}

		request_module("%s", "it913x");
		pdev = platform_device_register_data(&d->intf->dev, name,
						     PLATFORM_DEVID_AUTO,
						     &it913x_pdata,
						     sizeof(it913x_pdata));
		if (IS_ERR(pdev) || !pdev->dev.driver) {
			ret = -ENODEV;
			goto err;
		}
		if (!try_module_get(pdev->dev.driver->owner)) {
			platform_device_unregister(pdev);
			ret = -ENODEV;
			goto err;
		}

		state->platform_device_tuner[adap->id] = pdev;
		fe = adap->fe[0];
		break;
	}
	default:
		fe = NULL;
	}

	if (fe == NULL) {
		ret = -ENODEV;
		goto err;
	}

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}