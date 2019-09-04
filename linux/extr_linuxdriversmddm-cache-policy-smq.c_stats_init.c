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
struct stats {unsigned int hit_threshold; unsigned int hits; unsigned int misses; } ;

/* Variables and functions */

__attribute__((used)) static void stats_init(struct stats *s, unsigned nr_levels)
{
	s->hit_threshold = (nr_levels * 3u) / 4u;
	s->hits = 0u;
	s->misses = 0u;
}