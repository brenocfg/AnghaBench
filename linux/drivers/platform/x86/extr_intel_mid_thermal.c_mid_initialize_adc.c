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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ADC_CHNL_START_ADDR ; 
 scalar_t__ ADC_LOOP_MAX ; 
 int /*<<< orphan*/  INTEL_MSIC_ADC1CNTL3 ; 
 int /*<<< orphan*/  MSIC_ADCTHERM_MASK ; 
 scalar_t__ channel_index ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ find_free_channel () ; 
 int intel_msic_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int intel_msic_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int reset_stopbit (scalar_t__) ; 
 int set_up_therm_channel (scalar_t__) ; 

__attribute__((used)) static int mid_initialize_adc(struct device *dev)
{
	u8  data;
	u16 base_addr;
	int ret;

	/*
	 * Ensure that adctherm is disabled before we
	 * initialize the ADC
	 */
	ret = intel_msic_reg_read(INTEL_MSIC_ADC1CNTL3, &data);
	if (ret)
		return ret;

	data &= ~MSIC_ADCTHERM_MASK;
	ret = intel_msic_reg_write(INTEL_MSIC_ADC1CNTL3, data);
	if (ret)
		return ret;

	/* Index of the first channel in which the stop bit is set */
	channel_index = find_free_channel();
	if (channel_index < 0) {
		dev_err(dev, "No free ADC channels");
		return channel_index;
	}

	base_addr = ADC_CHNL_START_ADDR + channel_index;

	if (!(channel_index == 0 || channel_index == ADC_LOOP_MAX)) {
		/* Reset stop bit for channels other than 0 and 12 */
		ret = reset_stopbit(base_addr);
		if (ret)
			return ret;

		/* Index of the first free channel */
		base_addr++;
		channel_index++;
	}

	ret = set_up_therm_channel(base_addr);
	if (ret) {
		dev_err(dev, "unable to enable ADC");
		return ret;
	}
	dev_dbg(dev, "ADC initialization successful");
	return ret;
}