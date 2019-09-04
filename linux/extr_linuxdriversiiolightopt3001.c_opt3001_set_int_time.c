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
struct opt3001 {int int_time; int /*<<< orphan*/  client; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPT3001_CONFIGURATION ; 
 int OPT3001_CONFIGURATION_CT ; 
#define  OPT3001_INT_TIME_LONG 129 
#define  OPT3001_INT_TIME_SHORT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int opt3001_set_int_time(struct opt3001 *opt, int time)
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

	switch (time) {
	case OPT3001_INT_TIME_SHORT:
		reg &= ~OPT3001_CONFIGURATION_CT;
		opt->int_time = OPT3001_INT_TIME_SHORT;
		break;
	case OPT3001_INT_TIME_LONG:
		reg |= OPT3001_CONFIGURATION_CT;
		opt->int_time = OPT3001_INT_TIME_LONG;
		break;
	default:
		return -EINVAL;
	}

	return i2c_smbus_write_word_swapped(opt->client, OPT3001_CONFIGURATION,
			reg);
}