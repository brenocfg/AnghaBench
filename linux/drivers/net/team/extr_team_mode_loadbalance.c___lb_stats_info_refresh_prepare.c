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
struct lb_stats_info {int /*<<< orphan*/  stats; int /*<<< orphan*/  last_stats; } ;
struct lb_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __lb_stats_info_refresh_prepare(struct lb_stats_info *s_info)
{
	memcpy(&s_info->last_stats, &s_info->stats, sizeof(struct lb_stats));
	memset(&s_info->stats, 0, sizeof(struct lb_stats));
}