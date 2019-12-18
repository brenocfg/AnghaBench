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
struct pc87427_sio_data {int has_fanin; int has_fanout; } ;
struct pc87427_data {int fan_enabled; int pwm_enabled; int pwm_auto_ok; int temp_enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BANK_FC (int) ; 
 int /*<<< orphan*/  BANK_FM (int) ; 
 int /*<<< orphan*/  BANK_TM (int) ; 
 int FAN_STATUS_MONEN ; 
 int /*<<< orphan*/  LD_FAN ; 
 int /*<<< orphan*/  LD_TEMP ; 
 int /*<<< orphan*/  PC87427_REG_BANK ; 
 int /*<<< orphan*/  PC87427_REG_FAN_STATUS ; 
 int /*<<< orphan*/  PC87427_REG_PWM_ENABLE ; 
 int /*<<< orphan*/  PC87427_REG_TEMP_STATUS ; 
 int PWM_ENABLE_CTLEN ; 
 int PWM_ENABLE_MODE_MASK ; 
 int PWM_MODE_AUTO ; 
 int TEMP_STATUS_CHANEN ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 struct pc87427_data* dev_get_drvdata (struct device*) ; 
 struct pc87427_sio_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,char*) ; 
 int pc87427_read8 (struct pc87427_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pc87427_read8_bank (struct pc87427_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc87427_write8_bank (struct pc87427_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pc87427_init_device(struct device *dev)
{
	struct pc87427_sio_data *sio_data = dev_get_platdata(dev);
	struct pc87427_data *data = dev_get_drvdata(dev);
	int i;
	u8 reg;

	/* The FMC module should be ready */
	reg = pc87427_read8(data, LD_FAN, PC87427_REG_BANK);
	if (!(reg & 0x80))
		dev_warn(dev, "%s module not ready!\n", "FMC");

	/* Check which fans are enabled */
	for (i = 0; i < 8; i++) {
		if (!(sio_data->has_fanin & (1 << i)))	/* Not wired */
			continue;
		reg = pc87427_read8_bank(data, LD_FAN, BANK_FM(i),
					 PC87427_REG_FAN_STATUS);
		if (reg & FAN_STATUS_MONEN)
			data->fan_enabled |= (1 << i);
	}

	if (!data->fan_enabled) {
		dev_dbg(dev, "Enabling monitoring of all fans\n");
		for (i = 0; i < 8; i++) {
			if (!(sio_data->has_fanin & (1 << i)))	/* Not wired */
				continue;
			pc87427_write8_bank(data, LD_FAN, BANK_FM(i),
					    PC87427_REG_FAN_STATUS,
					    FAN_STATUS_MONEN);
		}
		data->fan_enabled = sio_data->has_fanin;
	}

	/* Check which PWM outputs are enabled */
	for (i = 0; i < 4; i++) {
		if (!(sio_data->has_fanout & (1 << i)))	/* Not wired */
			continue;
		reg = pc87427_read8_bank(data, LD_FAN, BANK_FC(i),
					 PC87427_REG_PWM_ENABLE);
		if (reg & PWM_ENABLE_CTLEN)
			data->pwm_enabled |= (1 << i);

		/*
		 * We don't expose an interface to reconfigure the automatic
		 * fan control mode, so only allow to return to this mode if
		 * it was originally set.
		 */
		if ((reg & PWM_ENABLE_MODE_MASK) == PWM_MODE_AUTO) {
			dev_dbg(dev, "PWM%d is in automatic control mode\n",
				i + 1);
			data->pwm_auto_ok |= (1 << i);
		}
	}

	/* The HMC module should be ready */
	reg = pc87427_read8(data, LD_TEMP, PC87427_REG_BANK);
	if (!(reg & 0x80))
		dev_warn(dev, "%s module not ready!\n", "HMC");

	/* Check which temperature channels are enabled */
	for (i = 0; i < 6; i++) {
		reg = pc87427_read8_bank(data, LD_TEMP, BANK_TM(i),
					 PC87427_REG_TEMP_STATUS);
		if (reg & TEMP_STATUS_CHANEN)
			data->temp_enabled |= (1 << i);
	}
}