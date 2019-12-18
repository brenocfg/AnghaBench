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
struct mlxsw_sp_acl_bf {unsigned int bank_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
mlxsw_sp_acl_bf_rule_count_index_get(struct mlxsw_sp_acl_bf *bf,
				     unsigned int erp_bank,
				     unsigned int bf_index)
{
	return erp_bank * bf->bank_size + bf_index;
}