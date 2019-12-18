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
typedef  int /*<<< orphan*/  u64 ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;
struct TYPE_3__ {int sysctl_ip_fwd_update_priority; } ;
struct TYPE_4__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MAX_RIFS ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_CORE_RES_VALID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_RGCR_LEN ; 
 TYPE_2__ init_net ; 
 int /*<<< orphan*/  mlxsw_reg_rgcr_max_router_interfaces_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_reg_rgcr_pack (char*,int,int) ; 
 int /*<<< orphan*/  mlxsw_reg_rgcr_usp_set (char*,int) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rgcr ; 

__attribute__((used)) static int __mlxsw_sp_router_init(struct mlxsw_sp *mlxsw_sp)
{
	bool usp = init_net.ipv4.sysctl_ip_fwd_update_priority;
	char rgcr_pl[MLXSW_REG_RGCR_LEN];
	u64 max_rifs;
	int err;

	if (!MLXSW_CORE_RES_VALID(mlxsw_sp->core, MAX_RIFS))
		return -EIO;
	max_rifs = MLXSW_CORE_RES_GET(mlxsw_sp->core, MAX_RIFS);

	mlxsw_reg_rgcr_pack(rgcr_pl, true, true);
	mlxsw_reg_rgcr_max_router_interfaces_set(rgcr_pl, max_rifs);
	mlxsw_reg_rgcr_usp_set(rgcr_pl, usp);
	err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(rgcr), rgcr_pl);
	if (err)
		return err;
	return 0;
}