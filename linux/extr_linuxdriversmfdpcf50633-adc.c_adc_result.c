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
struct pcf50633 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PCF50633_ADCS3_ADCDAT1L_MASK ; 
 int /*<<< orphan*/  PCF50633_REG_ADCS1 ; 
 int /*<<< orphan*/  PCF50633_REG_ADCS3 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int pcf50633_reg_read (struct pcf50633*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adc_result(struct pcf50633 *pcf)
{
	u8 adcs1, adcs3;
	u16 result;

	adcs1 = pcf50633_reg_read(pcf, PCF50633_REG_ADCS1);
	adcs3 = pcf50633_reg_read(pcf, PCF50633_REG_ADCS3);
	result = (adcs1 << 2) | (adcs3 & PCF50633_ADCS3_ADCDAT1L_MASK);

	dev_dbg(pcf->dev, "adc result = %d\n", result);

	return result;
}