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
struct mlxsw_sp_acl_ruleset {int ref_count; } ;

/* Variables and functions */

__attribute__((used)) static bool
mlxsw_sp_acl_ruleset_is_singular(const struct mlxsw_sp_acl_ruleset *ruleset)
{
	/* We hold a reference on ruleset ourselves */
	return ruleset->ref_count == 2;
}