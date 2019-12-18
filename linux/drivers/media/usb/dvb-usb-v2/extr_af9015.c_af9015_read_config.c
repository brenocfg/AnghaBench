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
struct req_t {int member_4; int member_5; int* member_6; int addr; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {TYPE_2__* udev; struct usb_interface* intf; } ;
struct af9015_state {int ir_mode; int dual_mode; int* af9013_i2c_addr; int* mt2060_if1; TYPE_3__* af9013_pdata; } ;
struct TYPE_6__ {int clk; int if_frequency; int spec_inv; int tuner; int /*<<< orphan*/ * gpio; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF9013_GPIO_LO ; 
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
 int AF9015_EEPROM_DEMOD2_I2C ; 
 int AF9015_EEPROM_IF1H ; 
 int AF9015_EEPROM_IF1L ; 
 int AF9015_EEPROM_IR_MODE ; 
 int AF9015_EEPROM_MT2060_IF1H ; 
 int AF9015_EEPROM_MT2060_IF1L ; 
 int AF9015_EEPROM_OFFSET ; 
 int AF9015_EEPROM_TS_MODE ; 
 int AF9015_EEPROM_TUNER_ID1 ; 
 int AF9015_EEPROM_XTAL_TYPE1 ; 
 int AF9015_I2C_DEMOD ; 
 int /*<<< orphan*/  AF9015_I2C_EEPROM ; 
 int ENODEV ; 
 int /*<<< orphan*/  READ_I2C ; 
 scalar_t__ USB_PID_AVERMEDIA_A850 ; 
 scalar_t__ USB_PID_AVERMEDIA_A850T ; 
 scalar_t__ USB_VID_AVERMEDIA ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 
 int af9015_eeprom_hash (struct dvb_usb_device*) ; 
 struct af9015_state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9015_read_config(struct dvb_usb_device *d)
{
	struct af9015_state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret;
	u8 val, i, offset = 0;
	struct req_t req = {READ_I2C, AF9015_I2C_EEPROM, 0, 0, 1, 1, &val};

	dev_dbg(&intf->dev, "\n");

	/* IR remote controller */
	req.addr = AF9015_EEPROM_IR_MODE;
	/* first message will timeout often due to possible hw bug */
	for (i = 0; i < 4; i++) {
		ret = af9015_ctrl_msg(d, &req);
		if (!ret)
			break;
	}
	if (ret)
		goto error;

	ret = af9015_eeprom_hash(d);
	if (ret)
		goto error;

	state->ir_mode = val;
	dev_dbg(&intf->dev, "ir mode %02x\n", val);

	/* TS mode - one or two receivers */
	req.addr = AF9015_EEPROM_TS_MODE;
	ret = af9015_ctrl_msg(d, &req);
	if (ret)
		goto error;

	state->dual_mode = val;
	dev_dbg(&intf->dev, "ts mode %02x\n", state->dual_mode);

	state->af9013_i2c_addr[0] = AF9015_I2C_DEMOD;

	if (state->dual_mode) {
		/* read 2nd demodulator I2C address */
		req.addr = AF9015_EEPROM_DEMOD2_I2C;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;

		state->af9013_i2c_addr[1] = val >> 1;
	}

	for (i = 0; i < state->dual_mode + 1; i++) {
		if (i == 1)
			offset = AF9015_EEPROM_OFFSET;
		/* xtal */
		req.addr = AF9015_EEPROM_XTAL_TYPE1 + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;
		switch (val) {
		case 0:
			state->af9013_pdata[i].clk = 28800000;
			break;
		case 1:
			state->af9013_pdata[i].clk = 20480000;
			break;
		case 2:
			state->af9013_pdata[i].clk = 28000000;
			break;
		case 3:
			state->af9013_pdata[i].clk = 25000000;
			break;
		}
		dev_dbg(&intf->dev, "[%d] xtal %02x, clk %u\n",
			i, val, state->af9013_pdata[i].clk);

		/* IF frequency */
		req.addr = AF9015_EEPROM_IF1H + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;

		state->af9013_pdata[i].if_frequency = val << 8;

		req.addr = AF9015_EEPROM_IF1L + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;

		state->af9013_pdata[i].if_frequency += val;
		state->af9013_pdata[i].if_frequency *= 1000;
		dev_dbg(&intf->dev, "[%d] if frequency %u\n",
			i, state->af9013_pdata[i].if_frequency);

		/* MT2060 IF1 */
		req.addr = AF9015_EEPROM_MT2060_IF1H  + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;
		state->mt2060_if1[i] = val << 8;
		req.addr = AF9015_EEPROM_MT2060_IF1L + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;
		state->mt2060_if1[i] += val;
		dev_dbg(&intf->dev, "[%d] MT2060 IF1 %u\n",
			i, state->mt2060_if1[i]);

		/* tuner */
		req.addr =  AF9015_EEPROM_TUNER_ID1 + offset;
		ret = af9015_ctrl_msg(d, &req);
		if (ret)
			goto error;
		switch (val) {
		case AF9013_TUNER_ENV77H11D5:
		case AF9013_TUNER_MT2060:
		case AF9013_TUNER_QT1010:
		case AF9013_TUNER_UNKNOWN:
		case AF9013_TUNER_MT2060_2:
		case AF9013_TUNER_TDA18271:
		case AF9013_TUNER_QT1010A:
		case AF9013_TUNER_TDA18218:
			state->af9013_pdata[i].spec_inv = 1;
			break;
		case AF9013_TUNER_MXL5003D:
		case AF9013_TUNER_MXL5005D:
		case AF9013_TUNER_MXL5005R:
		case AF9013_TUNER_MXL5007T:
			state->af9013_pdata[i].spec_inv = 0;
			break;
		case AF9013_TUNER_MC44S803:
			state->af9013_pdata[i].gpio[1] = AF9013_GPIO_LO;
			state->af9013_pdata[i].spec_inv = 1;
			break;
		default:
			dev_err(&intf->dev,
				"tuner id %02x not supported, please report!\n",
				val);
			return -ENODEV;
		}

		state->af9013_pdata[i].tuner = val;
		dev_dbg(&intf->dev, "[%d] tuner id %02x\n", i, val);
	}

error:
	if (ret)
		dev_err(&intf->dev, "eeprom read failed %d\n", ret);

	/*
	 * AverMedia AVerTV Volar Black HD (A850) device have bad EEPROM
	 * content :-( Override some wrong values here. Ditto for the
	 * AVerTV Red HD+ (A850T) device.
	 */
	if (le16_to_cpu(d->udev->descriptor.idVendor) == USB_VID_AVERMEDIA &&
	    ((le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_A850) ||
	    (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_A850T))) {
		dev_dbg(&intf->dev, "AverMedia A850: overriding config\n");
		/* disable dual mode */
		state->dual_mode = 0;

		/* set correct IF */
		state->af9013_pdata[0].if_frequency = 4570000;
	}

	return ret;
}