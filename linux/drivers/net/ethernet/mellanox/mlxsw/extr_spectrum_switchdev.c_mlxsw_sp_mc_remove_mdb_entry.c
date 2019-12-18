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
struct mlxsw_sp_mid {int in_hw; int /*<<< orphan*/  mid; int /*<<< orphan*/  fid; int /*<<< orphan*/  addr; } ;
struct mlxsw_sp {TYPE_1__* bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  mids_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_sp_port_mdb_op (struct mlxsw_sp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mlxsw_sp_mc_remove_mdb_entry(struct mlxsw_sp *mlxsw_sp,
					struct mlxsw_sp_mid *mid)
{
	if (!mid->in_hw)
		return 0;

	clear_bit(mid->mid, mlxsw_sp->bridge->mids_bitmap);
	mid->in_hw = false;
	return mlxsw_sp_port_mdb_op(mlxsw_sp, mid->addr, mid->fid, mid->mid,
				    false);
}