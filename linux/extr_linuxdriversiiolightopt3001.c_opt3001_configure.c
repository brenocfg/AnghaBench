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
typedef  int u16 ;
struct opt3001 {void* high_thresh_exp; void* high_thresh_mantissa; int /*<<< orphan*/  dev; int /*<<< orphan*/  client; void* low_thresh_exp; void* low_thresh_mantissa; int /*<<< orphan*/  int_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPT3001_CONFIGURATION ; 
 int OPT3001_CONFIGURATION_CT ; 
 int OPT3001_CONFIGURATION_FC_MASK ; 
 int OPT3001_CONFIGURATION_L ; 
 int OPT3001_CONFIGURATION_ME ; 
 int /*<<< orphan*/  OPT3001_CONFIGURATION_M_SHUTDOWN ; 
 int OPT3001_CONFIGURATION_POL ; 
 int OPT3001_CONFIGURATION_RN_AUTO ; 
 int OPT3001_CONFIGURATION_RN_MASK ; 
 int /*<<< orphan*/  OPT3001_HIGH_LIMIT ; 
 int /*<<< orphan*/  OPT3001_INT_TIME_LONG ; 
 int /*<<< orphan*/  OPT3001_INT_TIME_SHORT ; 
 int /*<<< orphan*/  OPT3001_LOW_LIMIT ; 
 void* OPT3001_REG_EXPONENT (int) ; 
 void* OPT3001_REG_MANTISSA (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  opt3001_set_mode (struct opt3001*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt3001_configure(struct opt3001 *opt)
{
	int ret;
	u16 reg;

	ret = i2c_smbus_read_word_swapped(opt->client, OPT3001_CONFIGURATION);
	if (ret < 0) {
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_CONFIGURATION);
		return ret;
	}

	reg = ret;

	/* Enable automatic full-scale setting mode */
	reg &= ~OPT3001_CONFIGURATION_RN_MASK;
	reg |= OPT3001_CONFIGURATION_RN_AUTO;

	/* Reflect status of the device's integration time setting */
	if (reg & OPT3001_CONFIGURATION_CT)
		opt->int_time = OPT3001_INT_TIME_LONG;
	else
		opt->int_time = OPT3001_INT_TIME_SHORT;

	/* Ensure device is in shutdown initially */
	opt3001_set_mode(opt, &reg, OPT3001_CONFIGURATION_M_SHUTDOWN);

	/* Configure for latched window-style comparison operation */
	reg |= OPT3001_CONFIGURATION_L;
	reg &= ~OPT3001_CONFIGURATION_POL;
	reg &= ~OPT3001_CONFIGURATION_ME;
	reg &= ~OPT3001_CONFIGURATION_FC_MASK;

	ret = i2c_smbus_write_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
	if (ret < 0) {
		dev_err(opt->dev, "failed to write register %02x\n",
				OPT3001_CONFIGURATION);
		return ret;
	}

	ret = i2c_smbus_read_word_swapped(opt->client, OPT3001_LOW_LIMIT);
	if (ret < 0) {
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_LOW_LIMIT);
		return ret;
	}

	opt->low_thresh_mantissa = OPT3001_REG_MANTISSA(ret);
	opt->low_thresh_exp = OPT3001_REG_EXPONENT(ret);

	ret = i2c_smbus_read_word_swapped(opt->client, OPT3001_HIGH_LIMIT);
	if (ret < 0) {
		dev_err(opt->dev, "failed to read register %02x\n",
				OPT3001_HIGH_LIMIT);
		return ret;
	}

	opt->high_thresh_mantissa = OPT3001_REG_MANTISSA(ret);
	opt->high_thresh_exp = OPT3001_REG_EXPONENT(ret);

	return 0;
}