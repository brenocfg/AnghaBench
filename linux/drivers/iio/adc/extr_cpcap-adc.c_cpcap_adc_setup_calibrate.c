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
struct cpcap_adc {int /*<<< orphan*/  reg; int /*<<< orphan*/  dev; } ;
typedef  enum cpcap_adc_channel { ____Placeholder_cpcap_adc_channel } cpcap_adc_channel ;

/* Variables and functions */
 int CPCAP_ADC_BATTI ; 
 int CPCAP_ADC_CHG_ISENSE ; 
 int CPCAP_BIT_ADA0 ; 
 int CPCAP_BIT_ADA1 ; 
 int CPCAP_BIT_ADA2 ; 
 unsigned int CPCAP_BIT_ADC_PS_FACTOR0 ; 
 unsigned int CPCAP_BIT_ADC_PS_FACTOR1 ; 
 unsigned int CPCAP_BIT_ADTRIG_DIS ; 
 unsigned int CPCAP_BIT_AD_SEL1 ; 
 unsigned int CPCAP_BIT_ASC ; 
 unsigned int CPCAP_BIT_ATO0 ; 
 unsigned int CPCAP_BIT_ATO1 ; 
 unsigned int CPCAP_BIT_ATO2 ; 
 unsigned int CPCAP_BIT_ATO3 ; 
 unsigned int CPCAP_BIT_ATOX ; 
 unsigned int CPCAP_BIT_ATOX_PS_FACTOR ; 
 unsigned int CPCAP_BIT_CAL_MODE ; 
 unsigned int CPCAP_BIT_RAND0 ; 
 unsigned int CPCAP_BIT_RAND1 ; 
 int /*<<< orphan*/  CPCAP_REG_ADCC1 ; 
 int /*<<< orphan*/  CPCAP_REG_ADCC2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void cpcap_adc_setup_calibrate(struct cpcap_adc *ddata,
				      enum cpcap_adc_channel chan)
{
	unsigned int value = 0;
	unsigned long timeout = jiffies + msecs_to_jiffies(3000);
	int error;

	if ((chan != CPCAP_ADC_CHG_ISENSE) &&
	    (chan != CPCAP_ADC_BATTI))
		return;

	value |= CPCAP_BIT_CAL_MODE | CPCAP_BIT_RAND0;
	value |= ((chan << 4) &
		  (CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 | CPCAP_BIT_ADA0));

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   CPCAP_BIT_CAL_MODE | CPCAP_BIT_ATOX |
				   CPCAP_BIT_ATO3 | CPCAP_BIT_ATO2 |
				   CPCAP_BIT_ATO1 | CPCAP_BIT_ATO0 |
				   CPCAP_BIT_ADA2 | CPCAP_BIT_ADA1 |
				   CPCAP_BIT_ADA0 | CPCAP_BIT_AD_SEL1 |
				   CPCAP_BIT_RAND1 | CPCAP_BIT_RAND0,
				   value);
	if (error)
		return;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ATOX_PS_FACTOR |
				   CPCAP_BIT_ADC_PS_FACTOR1 |
				   CPCAP_BIT_ADC_PS_FACTOR0,
				   0);
	if (error)
		return;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ADTRIG_DIS,
				   CPCAP_BIT_ADTRIG_DIS);
	if (error)
		return;

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC2,
				   CPCAP_BIT_ASC,
				   CPCAP_BIT_ASC);
	if (error)
		return;

	do {
		schedule_timeout_uninterruptible(1);
		error = regmap_read(ddata->reg, CPCAP_REG_ADCC2, &value);
		if (error)
			return;
	} while ((value & CPCAP_BIT_ASC) && time_before(jiffies, timeout));

	if (value & CPCAP_BIT_ASC)
		dev_err(ddata->dev,
			"Timeout waiting for calibration to complete\n");

	error = regmap_update_bits(ddata->reg, CPCAP_REG_ADCC1,
				   CPCAP_BIT_CAL_MODE, 0);
	if (error)
		return;
}