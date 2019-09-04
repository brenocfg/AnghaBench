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
#define  TSL2563_TIMING_100MS 130 
#define  TSL2563_TIMING_13MS 129 
#define  TSL2563_TIMING_400MS 128 
 int TSL2563_TIMING_GAIN16 ; 
 int TSL2563_TIMING_MASK ; 

__attribute__((used)) static int tsl2563_adc_shiftbits(u8 timing)
{
	int shift = 0;

	switch (timing & TSL2563_TIMING_MASK) {
	case TSL2563_TIMING_13MS:
		shift += 5;
		break;
	case TSL2563_TIMING_100MS:
		shift += 2;
		break;
	case TSL2563_TIMING_400MS:
		/* no-op */
		break;
	}

	if (!(timing & TSL2563_TIMING_GAIN16))
		shift += 4;

	return shift;
}