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
struct isl6421 {int /*<<< orphan*/  i2c; int /*<<< orphan*/  override_and; int /*<<< orphan*/  config; int /*<<< orphan*/  override_or; int /*<<< orphan*/  i2c_addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;
typedef  enum fe_sec_tone_mode { ____Placeholder_fe_sec_tone_mode } fe_sec_tone_mode ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  ISL6421_ENT1 ; 
#define  SEC_TONE_OFF 129 
#define  SEC_TONE_ON 128 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int isl6421_set_tone(struct dvb_frontend *fe,
			    enum fe_sec_tone_mode tone)
{
	struct isl6421 *isl6421 = (struct isl6421 *) fe->sec_priv;
	struct i2c_msg msg = { .addr = isl6421->i2c_addr, .flags = 0,
			       .buf = &isl6421->config,
			       .len = sizeof(isl6421->config) };

	switch (tone) {
	case SEC_TONE_ON:
		isl6421->config |= ISL6421_ENT1;
		break;
	case SEC_TONE_OFF:
		isl6421->config &= ~ISL6421_ENT1;
		break;
	default:
		return -EINVAL;
	}

	isl6421->config |= isl6421->override_or;
	isl6421->config &= isl6421->override_and;

	return (i2c_transfer(isl6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
}