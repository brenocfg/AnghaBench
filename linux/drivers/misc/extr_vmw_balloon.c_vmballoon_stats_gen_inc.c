#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmballoon {TYPE_1__* stats; } ;
typedef  enum vmballoon_stat_general { ____Placeholder_vmballoon_stat_general } vmballoon_stat_general ;
struct TYPE_2__ {int /*<<< orphan*/ * general_stat; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ is_vmballoon_stats_on () ; 

__attribute__((used)) static inline void vmballoon_stats_gen_inc(struct vmballoon *b,
					   enum vmballoon_stat_general stat)
{
	if (is_vmballoon_stats_on())
		atomic64_inc(&b->stats->general_stat[stat]);
}