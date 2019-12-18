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
struct cache_stats {int /*<<< orphan*/  writeback; int /*<<< orphan*/  demotion; int /*<<< orphan*/  promotion; } ;
typedef  enum policy_operation { ____Placeholder_policy_operation } policy_operation ;

/* Variables and functions */
#define  POLICY_DEMOTE 130 
#define  POLICY_PROMOTE 129 
#define  POLICY_WRITEBACK 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_stats(struct cache_stats *stats, enum policy_operation op)
{
	switch (op) {
	case POLICY_PROMOTE:
		atomic_inc(&stats->promotion);
		break;

	case POLICY_DEMOTE:
		atomic_inc(&stats->demotion);
		break;

	case POLICY_WRITEBACK:
		atomic_inc(&stats->writeback);
		break;
	}
}