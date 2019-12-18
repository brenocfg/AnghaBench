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
typedef  scalar_t__ u8 ;
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  erp_id_bitmap; } ;

/* Variables and functions */
 int ENOBUFS ; 
 scalar_t__ MLXSW_SP_ACL_ERP_MAX_PER_REGION ; 
 int /*<<< orphan*/  __set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mlxsw_sp_acl_erp_id_get(struct mlxsw_sp_acl_erp_table *erp_table,
				   u8 *p_id)
{
	u8 id;

	id = find_first_zero_bit(erp_table->erp_id_bitmap,
				 MLXSW_SP_ACL_ERP_MAX_PER_REGION);
	if (id < MLXSW_SP_ACL_ERP_MAX_PER_REGION) {
		__set_bit(id, erp_table->erp_id_bitmap);
		*p_id = id;
		return 0;
	}

	return -ENOBUFS;
}