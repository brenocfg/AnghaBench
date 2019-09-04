#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct mxl111sf_state {scalar_t__ chip_rev; int /*<<< orphan*/  tv; int /*<<< orphan*/  fe_lock; int /*<<< orphan*/  msg_lock; } ;
struct i2c_msg {int addr; int len; int* buf; int /*<<< orphan*/  flags; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_adap; } ;
typedef  int /*<<< orphan*/  eeprom ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 scalar_t__ MXL111SF_V6 ; 
 int /*<<< orphan*/  PIN_MUX_TS_SPI_IN_MODE_1 ; 
 struct mxl111sf_state* d_to_priv (struct dvb_usb_device*) ; 
 int get_chip_info (struct mxl111sf_state*) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxl111sf_config_pin_mux_modes (struct mxl111sf_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ mxl_fail (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  tveeprom_hauppauge_analog (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int mxl111sf_init(struct dvb_usb_device *d)
{
	struct mxl111sf_state *state = d_to_priv(d);
	int ret;
	static u8 eeprom[256];
	u8 reg = 0;
	struct i2c_msg msg[2] = {
		{ .addr = 0xa0 >> 1, .len = 1, .buf = &reg },
		{ .addr = 0xa0 >> 1, .flags = I2C_M_RD,
		  .len = sizeof(eeprom), .buf = eeprom },
	};

	mutex_init(&state->msg_lock);

	ret = get_chip_info(state);
	if (mxl_fail(ret))
		pr_err("failed to get chip info during probe");

	mutex_init(&state->fe_lock);

	if (state->chip_rev > MXL111SF_V6)
		mxl111sf_config_pin_mux_modes(state, PIN_MUX_TS_SPI_IN_MODE_1);

	ret = i2c_transfer(&d->i2c_adap, msg, 2);
	if (mxl_fail(ret))
		return 0;
	tveeprom_hauppauge_analog(&state->tv, (0x84 == eeprom[0xa0]) ?
				  eeprom + 0xa0 : eeprom + 0x80);
#if 0
	switch (state->tv.model) {
	case 117001:
	case 126001:
	case 138001:
		break;
	default:
		printk(KERN_WARNING "%s: warning: unknown hauppauge model #%d\n",
		       __func__, state->tv.model);
	}
#endif
	return 0;
}