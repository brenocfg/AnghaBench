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
typedef  int u32 ;
struct mxs_lradc_ts {unsigned int over_sample_cnt; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ LRADC_CH (unsigned int) ; 
 int LRADC_CH_ACCUMULATE ; 
 int LRADC_CH_VALUE_MASK ; 
 int LRADC_CH_VALUE_OFFSET ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static unsigned int mxs_lradc_ts_read_raw_channel(struct mxs_lradc_ts *ts,
						  unsigned int channel)
{
	u32 reg;
	unsigned int num_samples, val;

	reg = readl(ts->base + LRADC_CH(channel));
	if (reg & LRADC_CH_ACCUMULATE)
		num_samples = ts->over_sample_cnt;
	else
		num_samples = 1;

	val = (reg & LRADC_CH_VALUE_MASK) >> LRADC_CH_VALUE_OFFSET;
	return val / num_samples;
}