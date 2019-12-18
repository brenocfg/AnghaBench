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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlxsw_sp_vr {int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int /*<<< orphan*/  mlxsw_sp; int /*<<< orphan*/  dev; } ;
struct mlxsw_sp_rif_ipip_lb {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct mlxsw_sp_vr*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_sp_ipip_dev_ul_tb_id (int /*<<< orphan*/ ) ; 
 struct mlxsw_sp_vr* mlxsw_sp_vr_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u16 mlxsw_sp_ipip_lb_ul_vr_id(const struct mlxsw_sp_rif_ipip_lb *lb_rif)
{
	u32 ul_tb_id = mlxsw_sp_ipip_dev_ul_tb_id(lb_rif->common.dev);
	struct mlxsw_sp_vr *ul_vr;

	ul_vr = mlxsw_sp_vr_get(lb_rif->common.mlxsw_sp, ul_tb_id, NULL);
	if (WARN_ON(IS_ERR(ul_vr)))
		return 0;

	return ul_vr->id;
}