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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_acl_erp_key {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_acl_erp_delta_fill (struct mlxsw_sp_acl_erp_key const*,struct mlxsw_sp_acl_erp_key const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool mlxsw_sp_acl_erp_delta_check(void *priv, const void *parent_obj,
					 const void *obj)
{
	const struct mlxsw_sp_acl_erp_key *parent_key = parent_obj;
	const struct mlxsw_sp_acl_erp_key *key = obj;
	u16 delta_start;
	u8 delta_mask;
	int err;

	err = mlxsw_sp_acl_erp_delta_fill(parent_key, key,
					  &delta_start, &delta_mask);
	return err ? false : true;
}