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
struct stats {int min; int max; int sigma; int /*<<< orphan*/  samples; } ;
typedef  int s8 ;
typedef  int s16 ;

/* Variables and functions */
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline
void stats_add_sample(struct stats *stats, s8 sample)
{
	s8 min, max;
	s16 sigma;
	unsigned samples = atomic_read(&stats->samples);
	if (samples == 0) {	/* it was zero before, so we initialize */
		min = 127;
		max = -128;
		sigma = 0;
	} else {
		min = stats->min;
		max = stats->max;
		sigma = stats->sigma;
	}

	if (sample < min)	/* compute new values */
		min = sample;
	else if (sample > max)
		max = sample;
	sigma += sample;

	stats->min = min;	/* commit */
	stats->max = max;
	stats->sigma = sigma;
	if (atomic_add_return(1, &stats->samples) > 255) {
		/* wrapped around! reset */
		stats->sigma = sigma / 256;
		atomic_set(&stats->samples, 1);
	}
}