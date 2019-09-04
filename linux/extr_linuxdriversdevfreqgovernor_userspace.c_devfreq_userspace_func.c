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
struct userspace_data {unsigned long user_frequency; scalar_t__ valid; } ;
struct devfreq {unsigned long max_freq; unsigned long min_freq; unsigned long previous_freq; struct userspace_data* data; } ;

/* Variables and functions */

__attribute__((used)) static int devfreq_userspace_func(struct devfreq *df, unsigned long *freq)
{
	struct userspace_data *data = df->data;

	if (data->valid) {
		unsigned long adjusted_freq = data->user_frequency;

		if (df->max_freq && adjusted_freq > df->max_freq)
			adjusted_freq = df->max_freq;

		if (df->min_freq && adjusted_freq < df->min_freq)
			adjusted_freq = df->min_freq;

		*freq = adjusted_freq;
	} else {
		*freq = df->previous_freq; /* No user freq specified yet */
	}
	return 0;
}