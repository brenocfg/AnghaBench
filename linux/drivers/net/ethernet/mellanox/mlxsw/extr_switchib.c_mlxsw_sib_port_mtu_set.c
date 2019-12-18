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
typedef  int u16 ;
struct mlxsw_sib_port {int /*<<< orphan*/  local_port; struct mlxsw_sib* mlxsw_sib; } ;
struct mlxsw_sib {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_PMTU_LEN ; 
 int mlxsw_reg_pmtu_max_mtu_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_pmtu_pack (char*,int /*<<< orphan*/ ,int) ; 
 int mlxsw_reg_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pmtu ; 

__attribute__((used)) static int mlxsw_sib_port_mtu_set(struct mlxsw_sib_port *mlxsw_sib_port,
				  u16 mtu)
{
	struct mlxsw_sib *mlxsw_sib = mlxsw_sib_port->mlxsw_sib;
	char pmtu_pl[MLXSW_REG_PMTU_LEN];
	int max_mtu;
	int err;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sib_port->local_port, 0);
	err = mlxsw_reg_query(mlxsw_sib->core, MLXSW_REG(pmtu), pmtu_pl);
	if (err)
		return err;
	max_mtu = mlxsw_reg_pmtu_max_mtu_get(pmtu_pl);

	if (mtu > max_mtu)
		return -EINVAL;

	mlxsw_reg_pmtu_pack(pmtu_pl, mlxsw_sib_port->local_port, mtu);
	return mlxsw_reg_write(mlxsw_sib->core, MLXSW_REG(pmtu), pmtu_pl);
}