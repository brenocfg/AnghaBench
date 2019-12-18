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
struct mlxsw_sp_mr_vif {scalar_t__ rif; scalar_t__ dev; TYPE_1__* ops; } ;
struct TYPE_2__ {scalar_t__ (* is_regular ) (struct mlxsw_sp_mr_vif const*) ;} ;

/* Variables and functions */
 scalar_t__ stub1 (struct mlxsw_sp_mr_vif const*) ; 

__attribute__((used)) static bool mlxsw_sp_mr_vif_valid(const struct mlxsw_sp_mr_vif *vif)
{
	return vif->ops->is_regular(vif) && vif->dev && vif->rif;
}