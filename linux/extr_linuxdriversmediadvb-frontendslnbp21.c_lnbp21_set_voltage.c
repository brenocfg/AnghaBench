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
struct lnbp21 {int config; int override_or; int override_and; int /*<<< orphan*/  i2c; int /*<<< orphan*/  i2c_addr; } ;
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int LNBP21_EN ; 
 int LNBP21_VSEL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int lnbp21_set_voltage(struct dvb_frontend *fe,
			      enum fe_sec_voltage voltage)
{
	struct lnbp21 *lnbp21 = (struct lnbp21 *) fe->sec_priv;
	struct i2c_msg msg = {	.addr = lnbp21->i2c_addr, .flags = 0,
				.buf = &lnbp21->config,
				.len = sizeof(lnbp21->config) };

	lnbp21->config &= ~(LNBP21_VSEL | LNBP21_EN);

	switch(voltage) {
	case SEC_VOLTAGE_OFF:
		break;
	case SEC_VOLTAGE_13:
		lnbp21->config |= LNBP21_EN;
		break;
	case SEC_VOLTAGE_18:
		lnbp21->config |= (LNBP21_EN | LNBP21_VSEL);
		break;
	default:
		return -EINVAL;
	}

	lnbp21->config |= lnbp21->override_or;
	lnbp21->config &= lnbp21->override_and;

	return (i2c_transfer(lnbp21->i2c, &msg, 1) == 1) ? 0 : -EIO;
}