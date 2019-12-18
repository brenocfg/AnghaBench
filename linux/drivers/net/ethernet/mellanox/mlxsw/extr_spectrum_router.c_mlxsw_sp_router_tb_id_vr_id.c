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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_vr {int /*<<< orphan*/  id; } ;
struct mlxsw_sp {int dummy; } ;

/* Variables and functions */
 int ESRCH ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_find (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 

int mlxsw_sp_router_tb_id_vr_id(struct mlxsw_sp *mlxsw_sp, u32 tb_id,
				u16 *vr_id)
{
	struct mlxsw_sp_vr *vr;

	vr = mlxsw_sp_vr_find(mlxsw_sp, tb_id);
	if (!vr)
		return -ESRCH;
	*vr_id = vr->id;

	return 0;
}