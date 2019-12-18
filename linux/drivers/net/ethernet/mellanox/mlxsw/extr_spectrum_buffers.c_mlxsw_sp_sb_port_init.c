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
struct mlxsw_sp_sb_port {struct mlxsw_sp_sb_pm* pms; } ;
struct mlxsw_sp_sb_pm {int dummy; } ;
struct mlxsw_sp {TYPE_1__* sb_vals; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mlxsw_sp_sb_pm* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlxsw_sp_sb_port_init(struct mlxsw_sp *mlxsw_sp,
				 struct mlxsw_sp_sb_port *sb_port)
{
	struct mlxsw_sp_sb_pm *pms;

	pms = kcalloc(mlxsw_sp->sb_vals->pool_count, sizeof(*pms),
		      GFP_KERNEL);
	if (!pms)
		return -ENOMEM;
	sb_port->pms = pms;
	return 0;
}