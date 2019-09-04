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
struct stats {unsigned int hit_threshold; int /*<<< orphan*/  misses; int /*<<< orphan*/  hits; } ;

/* Variables and functions */

__attribute__((used)) static void stats_level_accessed(struct stats *s, unsigned level)
{
	if (level >= s->hit_threshold)
		s->hits++;
	else
		s->misses++;
}