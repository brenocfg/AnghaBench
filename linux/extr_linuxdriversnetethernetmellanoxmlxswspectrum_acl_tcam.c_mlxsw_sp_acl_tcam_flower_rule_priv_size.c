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
struct mlxsw_sp_acl_tcam_flower_rule {int dummy; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 size_t mlxsw_sp_acl_tcam_entry_priv_size (struct mlxsw_sp*) ; 

__attribute__((used)) static size_t mlxsw_sp_acl_tcam_flower_rule_priv_size(struct mlxsw_sp *mlxsw_sp)
{
	return sizeof(struct mlxsw_sp_acl_tcam_flower_rule) +
	       mlxsw_sp_acl_tcam_entry_priv_size(mlxsw_sp);
}