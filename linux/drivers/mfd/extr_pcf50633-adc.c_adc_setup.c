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
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int PCF50633_ADCC1_ADCMUX_MASK ; 
 int PCF50633_ADCC1_ADCSTART ; 
 int PCF50633_ADCC1_RES_10BIT ; 
 int /*<<< orphan*/  PCF50633_REG_ADCC1 ; 
 int /*<<< orphan*/  PCF50633_REG_ADCC2 ; 
 int /*<<< orphan*/  PCF50633_REG_ADCC3 ; 
 int /*<<< orphan*/  pcf50633_reg_write (struct pcf50633*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void adc_setup(struct pcf50633 *pcf, int channel, int avg)
{
	channel &= PCF50633_ADCC1_ADCMUX_MASK;

	/* kill ratiometric, but enable ACCSW biasing */
	pcf50633_reg_write(pcf, PCF50633_REG_ADCC2, 0x00);
	pcf50633_reg_write(pcf, PCF50633_REG_ADCC3, 0x01);

	/* start ADC conversion on selected channel */
	pcf50633_reg_write(pcf, PCF50633_REG_ADCC1, channel | avg |
		    PCF50633_ADCC1_ADCSTART | PCF50633_ADCC1_RES_10BIT);
}