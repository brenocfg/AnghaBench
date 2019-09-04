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
struct TYPE_2__ {unsigned long interval; int /*<<< orphan*/  dw; } ;
struct mlxsw_sp_acl {TYPE_1__ rule_activity_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_core_schedule_dw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 

__attribute__((used)) static void mlxsw_sp_acl_rule_activity_work_schedule(struct mlxsw_sp_acl *acl)
{
	unsigned long interval = acl->rule_activity_update.interval;

	mlxsw_core_schedule_dw(&acl->rule_activity_update.dw,
			       msecs_to_jiffies(interval));
}