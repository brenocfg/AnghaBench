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
typedef  size_t u32 ;
typedef  int u16 ;

/* Variables and functions */
 size_t DIV_ROUND_CLOSEST (int,size_t) ; 
 size_t INA3221_CONFIG_AVG (int) ; 
 int INA3221_CONFIG_CHs_EN_MASK ; 
 size_t hweight16 (int) ; 
 size_t* ina3221_avg_samples ; 

__attribute__((used)) static inline u32 ina3221_interval_ms_to_conv_time(u16 config, int interval)
{
	u32 channels = hweight16(config & INA3221_CONFIG_CHs_EN_MASK);
	u32 samples_idx = INA3221_CONFIG_AVG(config);
	u32 samples = ina3221_avg_samples[samples_idx];

	/* Bisect the result to Bus and Shunt conversion times */
	return DIV_ROUND_CLOSEST(interval * 1000 / 2, channels * samples);
}