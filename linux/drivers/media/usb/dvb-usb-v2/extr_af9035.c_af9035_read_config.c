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
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {int* af9033_i2c_addr; int it930x_addresses; int chip_type; int chip_version; int ir_mode; int ir_type; int* eeprom; int dual_mode; int no_read; TYPE_3__* af9033_config; scalar_t__ no_eeprom; } ;
struct dvb_usb_device {TYPE_2__* udev; struct usb_interface* intf; } ;
struct TYPE_6__ {int dyn0_clk; int tuner; int spec_inv; int /*<<< orphan*/  clock; int /*<<< orphan*/  ts_mode; void* adc_multiplier; } ;
struct TYPE_4__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 void* AF9033_ADC_MULTIPLIER_2X ; 
 int /*<<< orphan*/  AF9033_TS_MODE_SERIAL ; 
 int /*<<< orphan*/  AF9033_TS_MODE_USB ; 
#define  AF9033_TUNER_FC0011 141 
#define  AF9033_TUNER_FC0012 140 
#define  AF9033_TUNER_FC2580 139 
#define  AF9033_TUNER_IT9135_38 138 
#define  AF9033_TUNER_IT9135_51 137 
#define  AF9033_TUNER_IT9135_52 136 
#define  AF9033_TUNER_IT9135_60 135 
#define  AF9033_TUNER_IT9135_61 134 
#define  AF9033_TUNER_IT9135_62 133 
#define  AF9033_TUNER_MXL5007T 132 
#define  AF9033_TUNER_TDA18218 131 
#define  AF9033_TUNER_TUA9001 130 
 int ARRAY_SIZE (TYPE_3__*) ; 
 unsigned int EEPROM_1_IF_H ; 
 unsigned int EEPROM_1_IF_L ; 
 unsigned int EEPROM_1_TUNER_ID ; 
 size_t EEPROM_2ND_DEMOD_ADDR ; 
 size_t EEPROM_IR_MODE ; 
 size_t EEPROM_IR_TYPE ; 
#define  USB_PID_AVERMEDIA_A867 129 
 int USB_PID_AVERMEDIA_TD310 ; 
#define  USB_PID_AVERMEDIA_TWINSTAR 128 
 int USB_VID_AVERMEDIA ; 
 int af9035_rd_reg (struct dvb_usb_device*,int,int*) ; 
 int /*<<< orphan*/ * clock_lut_af9035 ; 
 int /*<<< orphan*/ * clock_lut_it9135 ; 
 struct state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int af9035_read_config(struct dvb_usb_device *d)
{
	struct usb_interface *intf = d->intf;
	struct state *state = d_to_priv(d);
	int ret, i;
	u8 tmp;
	u16 tmp16;

	/* Demod I2C address */
	state->af9033_i2c_addr[0] = 0x1c;
	state->af9033_i2c_addr[1] = 0x1d;
	state->af9033_config[0].adc_multiplier = AF9033_ADC_MULTIPLIER_2X;
	state->af9033_config[1].adc_multiplier = AF9033_ADC_MULTIPLIER_2X;
	state->af9033_config[0].ts_mode = AF9033_TS_MODE_USB;
	state->af9033_config[1].ts_mode = AF9033_TS_MODE_SERIAL;
	state->it930x_addresses = 0;

	if (state->chip_type == 0x9135) {
		/* feed clock for integrated RF tuner */
		state->af9033_config[0].dyn0_clk = true;
		state->af9033_config[1].dyn0_clk = true;

		if (state->chip_version == 0x02) {
			state->af9033_config[0].tuner = AF9033_TUNER_IT9135_60;
			state->af9033_config[1].tuner = AF9033_TUNER_IT9135_60;
		} else {
			state->af9033_config[0].tuner = AF9033_TUNER_IT9135_38;
			state->af9033_config[1].tuner = AF9033_TUNER_IT9135_38;
		}

		if (state->no_eeprom) {
			/* Remote controller to NEC polling by default */
			state->ir_mode = 0x05;
			state->ir_type = 0x00;

			goto skip_eeprom;
		}
	} else if (state->chip_type == 0x9306) {
		/*
		 * IT930x is an USB bridge, only single demod-single tuner
		 * configurations seen so far.
		 */
		if ((le16_to_cpu(d->udev->descriptor.idVendor) == USB_VID_AVERMEDIA) &&
		    (le16_to_cpu(d->udev->descriptor.idProduct) == USB_PID_AVERMEDIA_TD310)) {
			state->it930x_addresses = 1;
		}
		return 0;
	}

	/* Remote controller */
	state->ir_mode = state->eeprom[EEPROM_IR_MODE];
	state->ir_type = state->eeprom[EEPROM_IR_TYPE];

	if (state->dual_mode) {
		/* Read 2nd demodulator I2C address. 8-bit format on eeprom */
		tmp = state->eeprom[EEPROM_2ND_DEMOD_ADDR];
		if (tmp)
			state->af9033_i2c_addr[1] = tmp >> 1;

		dev_dbg(&intf->dev, "2nd demod I2C addr=%02x\n",
			state->af9033_i2c_addr[1]);
	}

	for (i = 0; i < state->dual_mode + 1; i++) {
		unsigned int eeprom_offset = 0;

		/* tuner */
		tmp = state->eeprom[EEPROM_1_TUNER_ID + eeprom_offset];
		dev_dbg(&intf->dev, "[%d]tuner=%02x\n", i, tmp);

		/* tuner sanity check */
		if (state->chip_type == 0x9135) {
			if (state->chip_version == 0x02) {
				/* IT9135 BX (v2) */
				switch (tmp) {
				case AF9033_TUNER_IT9135_60:
				case AF9033_TUNER_IT9135_61:
				case AF9033_TUNER_IT9135_62:
					state->af9033_config[i].tuner = tmp;
					break;
				}
			} else {
				/* IT9135 AX (v1) */
				switch (tmp) {
				case AF9033_TUNER_IT9135_38:
				case AF9033_TUNER_IT9135_51:
				case AF9033_TUNER_IT9135_52:
					state->af9033_config[i].tuner = tmp;
					break;
				}
			}
		} else {
			/* AF9035 */
			state->af9033_config[i].tuner = tmp;
		}

		if (state->af9033_config[i].tuner != tmp) {
			dev_info(&intf->dev, "[%d] overriding tuner from %02x to %02x\n",
				 i, tmp, state->af9033_config[i].tuner);
		}

		switch (state->af9033_config[i].tuner) {
		case AF9033_TUNER_TUA9001:
		case AF9033_TUNER_FC0011:
		case AF9033_TUNER_MXL5007T:
		case AF9033_TUNER_TDA18218:
		case AF9033_TUNER_FC2580:
		case AF9033_TUNER_FC0012:
			state->af9033_config[i].spec_inv = 1;
			break;
		case AF9033_TUNER_IT9135_38:
		case AF9033_TUNER_IT9135_51:
		case AF9033_TUNER_IT9135_52:
		case AF9033_TUNER_IT9135_60:
		case AF9033_TUNER_IT9135_61:
		case AF9033_TUNER_IT9135_62:
			break;
		default:
			dev_warn(&intf->dev, "tuner id=%02x not supported, please report!",
				 tmp);
		}

		/* disable dual mode if driver does not support it */
		if (i == 1)
			switch (state->af9033_config[i].tuner) {
			case AF9033_TUNER_FC0012:
			case AF9033_TUNER_IT9135_38:
			case AF9033_TUNER_IT9135_51:
			case AF9033_TUNER_IT9135_52:
			case AF9033_TUNER_IT9135_60:
			case AF9033_TUNER_IT9135_61:
			case AF9033_TUNER_IT9135_62:
			case AF9033_TUNER_MXL5007T:
				break;
			default:
				state->dual_mode = false;
				dev_info(&intf->dev, "driver does not support 2nd tuner and will disable it");
		}

		/* tuner IF frequency */
		tmp = state->eeprom[EEPROM_1_IF_L + eeprom_offset];
		tmp16 = tmp << 0;
		tmp = state->eeprom[EEPROM_1_IF_H + eeprom_offset];
		tmp16 |= tmp << 8;
		dev_dbg(&intf->dev, "[%d]IF=%d\n", i, tmp16);

		eeprom_offset += 0x10; /* shift for the 2nd tuner params */
	}

skip_eeprom:
	/* get demod clock */
	ret = af9035_rd_reg(d, 0x00d800, &tmp);
	if (ret < 0)
		goto err;

	tmp = (tmp >> 0) & 0x0f;

	for (i = 0; i < ARRAY_SIZE(state->af9033_config); i++) {
		if (state->chip_type == 0x9135)
			state->af9033_config[i].clock = clock_lut_it9135[tmp];
		else
			state->af9033_config[i].clock = clock_lut_af9035[tmp];
	}

	state->no_read = false;
	/* Some MXL5007T devices cannot properly handle tuner I2C read ops. */
	if (state->af9033_config[0].tuner == AF9033_TUNER_MXL5007T &&
		le16_to_cpu(d->udev->descriptor.idVendor) == USB_VID_AVERMEDIA)

		switch (le16_to_cpu(d->udev->descriptor.idProduct)) {
		case USB_PID_AVERMEDIA_A867:
		case USB_PID_AVERMEDIA_TWINSTAR:
			dev_info(&intf->dev,
				 "Device may have issues with I2C read operations. Enabling fix.\n");
			state->no_read = true;
			break;
		}

	return 0;

err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}