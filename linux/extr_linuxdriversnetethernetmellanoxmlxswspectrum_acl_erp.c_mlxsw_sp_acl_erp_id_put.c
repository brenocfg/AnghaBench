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
struct mlxsw_sp_acl_erp_table {int /*<<< orphan*/  erp_id_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlxsw_sp_acl_erp_id_put(struct mlxsw_sp_acl_erp_table *erp_table,
				    u8 id)
{
	__clear_bit(id, erp_table->erp_id_bitmap);
}