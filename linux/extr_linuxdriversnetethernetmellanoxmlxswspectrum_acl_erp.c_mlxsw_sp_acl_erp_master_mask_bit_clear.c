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
struct mlxsw_sp_acl_erp_master_mask {scalar_t__* count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlxsw_sp_acl_erp_master_mask_bit_clear(unsigned long bit,
				       struct mlxsw_sp_acl_erp_master_mask *mask)
{
	if (--mask->count[bit] == 0)
		__clear_bit(bit, mask->bitmap);
}