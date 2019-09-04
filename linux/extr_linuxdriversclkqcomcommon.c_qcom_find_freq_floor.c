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
struct freq_tbl {long freq; } ;

/* Variables and functions */

const struct freq_tbl *qcom_find_freq_floor(const struct freq_tbl *f,
					    unsigned long rate)
{
	const struct freq_tbl *best = NULL;

	for ( ; f->freq; f++) {
		if (rate >= f->freq)
			best = f;
		else
			break;
	}

	return best;
}