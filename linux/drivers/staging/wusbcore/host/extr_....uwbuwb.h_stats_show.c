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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,int,int,int) ; 

__attribute__((used)) static inline ssize_t stats_show(struct stats *stats, char *buf)
{
	int min, max, avg;
	int samples = atomic_read(&stats->samples);
	if (samples == 0)
		min = max = avg = 0;
	else {
		min = stats->min;
		max = stats->max;
		avg = stats->sigma / samples;
	}
	return scnprintf(buf, PAGE_SIZE, "%d %d %d\n", min, max, avg);
}