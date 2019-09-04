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

/* Variables and functions */
 int EBUSY ; 
 int TS5500_ADC_CONV_BUSY ; 
 int /*<<< orphan*/  TS5500_ADC_CONV_BUSY_ADDR ; 
 int /*<<< orphan*/  TS5500_ADC_CONV_DELAY ; 
 int /*<<< orphan*/  TS5500_ADC_CONV_INIT_LSB_ADDR ; 
 int /*<<< orphan*/  TS5500_ADC_CONV_MSB_ADDR ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ts5500_adc_convert(u8 ctrl)
{
	u8 lsb, msb;

	/* Start conversion (ensure the 3 MSB are set to 0) */
	outb(ctrl & 0x1f, TS5500_ADC_CONV_INIT_LSB_ADDR);

	/*
	 * The platform has CPLD logic driving the A/D converter.
	 * The conversion must complete within 11 microseconds,
	 * otherwise we have to re-initiate a conversion.
	 */
	udelay(TS5500_ADC_CONV_DELAY);
	if (inb(TS5500_ADC_CONV_BUSY_ADDR) & TS5500_ADC_CONV_BUSY)
		return -EBUSY;

	/* Read the raw data */
	lsb = inb(TS5500_ADC_CONV_INIT_LSB_ADDR);
	msb = inb(TS5500_ADC_CONV_MSB_ADDR);

	return (msb << 8) | lsb;
}