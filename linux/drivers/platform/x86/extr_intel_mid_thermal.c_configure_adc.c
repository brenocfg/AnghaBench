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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MSIC_ADC1CNTL1 ; 
 int MSIC_ADC_ENBL ; 
 int MSIC_ADC_START ; 
 int intel_msic_reg_read (int /*<<< orphan*/ ,int*) ; 
 int intel_msic_reg_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int configure_adc(int val)
{
	int ret;
	uint8_t data;

	ret = intel_msic_reg_read(INTEL_MSIC_ADC1CNTL1, &data);
	if (ret)
		return ret;

	if (val) {
		/* Enable and start the ADC */
		data |= (MSIC_ADC_ENBL | MSIC_ADC_START);
	} else {
		/* Just stop the ADC */
		data &= (~MSIC_ADC_START);
	}
	return intel_msic_reg_write(INTEL_MSIC_ADC1CNTL1, data);
}