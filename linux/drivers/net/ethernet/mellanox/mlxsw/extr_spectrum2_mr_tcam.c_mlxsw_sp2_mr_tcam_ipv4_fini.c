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
struct mlxsw_sp2_mr_tcam {int /*<<< orphan*/  ruleset4; int /*<<< orphan*/  mlxsw_sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_sp_acl_ruleset_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp2_mr_tcam_ipv4_fini(struct mlxsw_sp2_mr_tcam *mr_tcam)
{
	mlxsw_sp_acl_ruleset_put(mr_tcam->mlxsw_sp, mr_tcam->ruleset4);
}