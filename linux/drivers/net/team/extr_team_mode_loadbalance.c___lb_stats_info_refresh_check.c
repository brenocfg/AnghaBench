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
struct team {int dummy; } ;
struct lb_stats_info {int /*<<< orphan*/  opt_inst_info; int /*<<< orphan*/  stats; int /*<<< orphan*/  last_stats; } ;
struct lb_stats {int dummy; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  team_option_inst_set_change (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __lb_stats_info_refresh_check(struct lb_stats_info *s_info,
					  struct team *team)
{
	if (memcmp(&s_info->last_stats, &s_info->stats,
	    sizeof(struct lb_stats))) {
		team_option_inst_set_change(s_info->opt_inst_info);
		return true;
	}
	return false;
}