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
struct devfreq {unsigned long max_freq; } ;

/* Variables and functions */
 unsigned long UINT_MAX ; 

__attribute__((used)) static int devfreq_performance_func(struct devfreq *df,
				    unsigned long *freq)
{
	/*
	 * target callback should be able to get floor value as
	 * said in devfreq.h
	 */
	if (!df->max_freq)
		*freq = UINT_MAX;
	else
		*freq = df->max_freq;
	return 0;
}