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
struct pblk {int sec_per_write; int min_write_pgs; } ;

/* Variables and functions */

int pblk_calc_secs(struct pblk *pblk, unsigned long secs_avail,
		   unsigned long secs_to_flush)
{
	int max = pblk->sec_per_write;
	int min = pblk->min_write_pgs;
	int secs_to_sync = 0;

	if (secs_avail >= max)
		secs_to_sync = max;
	else if (secs_avail >= min)
		secs_to_sync = min * (secs_avail / min);
	else if (secs_to_flush)
		secs_to_sync = min;

	return secs_to_sync;
}