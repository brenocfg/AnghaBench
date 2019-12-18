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
typedef  int u64 ;
struct ni_gpct {int clock_period_ps; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NI_GPCT_CLOCK_SRC_SELECT_MASK ; 
#define  NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS 134 
 unsigned int NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK ; 
#define  NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS 133 
#define  NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS 132 
#define  NI_GPCT_PXI10_CLOCK_SRC_BITS 131 
#define  NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS 130 
#define  NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS 129 
#define  NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS 128 

__attribute__((used)) static int ni_tio_clock_period_ps(const struct ni_gpct *counter,
				  unsigned int generic_clock_source,
				  u64 *period_ps)
{
	u64 clock_period_ps;

	switch (generic_clock_source & NI_GPCT_CLOCK_SRC_SELECT_MASK) {
	case NI_GPCT_TIMEBASE_1_CLOCK_SRC_BITS:
		clock_period_ps = 50000;
		break;
	case NI_GPCT_TIMEBASE_2_CLOCK_SRC_BITS:
		clock_period_ps = 10000000;
		break;
	case NI_GPCT_TIMEBASE_3_CLOCK_SRC_BITS:
		clock_period_ps = 12500;
		break;
	case NI_GPCT_PXI10_CLOCK_SRC_BITS:
		clock_period_ps = 100000;
		break;
	default:
		/*
		 * clock period is specified by user with prescaling
		 * already taken into account.
		 */
		*period_ps = counter->clock_period_ps;
		return 0;
	}

	switch (generic_clock_source & NI_GPCT_PRESCALE_MODE_CLOCK_SRC_MASK) {
	case NI_GPCT_NO_PRESCALE_CLOCK_SRC_BITS:
		break;
	case NI_GPCT_PRESCALE_X2_CLOCK_SRC_BITS:
		clock_period_ps *= 2;
		break;
	case NI_GPCT_PRESCALE_X8_CLOCK_SRC_BITS:
		clock_period_ps *= 8;
		break;
	default:
		return -EINVAL;
	}
	*period_ps = clock_period_ps;
	return 0;
}