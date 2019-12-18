#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct mlxsw_sp {TYPE_2__* sb_vals; } ;
struct TYPE_4__ {int pool_count; TYPE_1__* pool_dess; } ;
struct TYPE_3__ {scalar_t__ dir; } ;

/* Variables and functions */
 scalar_t__ MLXSW_REG_SBXX_DIR_INGRESS ; 
 int /*<<< orphan*/  WARN (int,char*) ; 

__attribute__((used)) static void mlxsw_sp_pool_count(struct mlxsw_sp *mlxsw_sp,
				u16 *p_ingress_len, u16 *p_egress_len)
{
	int i;

	for (i = 0; i < mlxsw_sp->sb_vals->pool_count; ++i) {
		if (mlxsw_sp->sb_vals->pool_dess[i].dir ==
		    MLXSW_REG_SBXX_DIR_INGRESS)
			(*p_ingress_len)++;
		else
			(*p_egress_len)++;
	}

	WARN(*p_egress_len == 0, "No egress pools\n");
}