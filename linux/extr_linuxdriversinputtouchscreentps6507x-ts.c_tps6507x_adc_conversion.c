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
typedef  int u16 ;
struct tps6507x_ts {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int TPS6507X_ADCONFIG_CONVERT_TS ; 
 int TPS6507X_ADCONFIG_START_CONVERSION ; 
 int /*<<< orphan*/  TPS6507X_REG_ADCONFIG ; 
 int /*<<< orphan*/  TPS6507X_REG_ADRESULT_1 ; 
 int /*<<< orphan*/  TPS6507X_REG_ADRESULT_2 ; 
 int TPS6507X_REG_ADRESULT_2_MASK ; 
 int /*<<< orphan*/  TPS6507X_REG_TSCMODE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tps6507x_read_u8 (struct tps6507x_ts*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ tps6507x_write_u8 (struct tps6507x_ts*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 tps6507x_adc_conversion(struct tps6507x_ts *tsc,
				   u8 tsc_mode, u16 *value)
{
	s32 ret;
	u8 adc_status;
	u8 result;

	/* Route input signal to A/D converter */

	ret = tps6507x_write_u8(tsc, TPS6507X_REG_TSCMODE, tsc_mode);
	if (ret) {
		dev_err(tsc->dev, "TSC mode read failed\n");
		goto err;
	}

	/* Start A/D conversion */

	ret = tps6507x_write_u8(tsc, TPS6507X_REG_ADCONFIG,
				TPS6507X_ADCONFIG_CONVERT_TS);
	if (ret) {
		dev_err(tsc->dev, "ADC config write failed\n");
		return ret;
	}

	do {
		ret = tps6507x_read_u8(tsc, TPS6507X_REG_ADCONFIG,
				       &adc_status);
		if (ret) {
			dev_err(tsc->dev, "ADC config read failed\n");
			goto err;
		}
	} while (adc_status & TPS6507X_ADCONFIG_START_CONVERSION);

	ret = tps6507x_read_u8(tsc, TPS6507X_REG_ADRESULT_2, &result);
	if (ret) {
		dev_err(tsc->dev, "ADC result 2 read failed\n");
		goto err;
	}

	*value = (result & TPS6507X_REG_ADRESULT_2_MASK) << 8;

	ret = tps6507x_read_u8(tsc, TPS6507X_REG_ADRESULT_1, &result);
	if (ret) {
		dev_err(tsc->dev, "ADC result 1 read failed\n");
		goto err;
	}

	*value |= result;

	dev_dbg(tsc->dev, "TSC channel %d = 0x%X\n", tsc_mode, *value);

err:
	return ret;
}