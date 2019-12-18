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
struct mlxsw_sp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  local_port; struct mlxsw_sp* mlxsw_sp; } ;
struct mlxsw_sp {int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLXSW_REG (int /*<<< orphan*/ ) ; 
 int MLXSW_REG_SBIB_LEN ; 
 int /*<<< orphan*/  mlxsw_reg_sbib_pack (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlxsw_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mlxsw_sp_span_is_egress_mirror (struct mlxsw_sp_port*) ; 
 int /*<<< orphan*/  mlxsw_sp_span_mtu_to_buffsize (struct mlxsw_sp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sbib ; 

int mlxsw_sp_span_port_mtu_update(struct mlxsw_sp_port *port, u16 mtu)
{
	struct mlxsw_sp *mlxsw_sp = port->mlxsw_sp;
	char sbib_pl[MLXSW_REG_SBIB_LEN];
	int err;

	/* If port is egress mirrored, the shared buffer size should be
	 * updated according to the mtu value
	 */
	if (mlxsw_sp_span_is_egress_mirror(port)) {
		u32 buffsize = mlxsw_sp_span_mtu_to_buffsize(mlxsw_sp, mtu);

		mlxsw_reg_sbib_pack(sbib_pl, port->local_port, buffsize);
		err = mlxsw_reg_write(mlxsw_sp->core, MLXSW_REG(sbib), sbib_pl);
		if (err) {
			netdev_err(port->dev, "Could not update shared buffer for mirroring\n");
			return err;
		}
	}

	return 0;
}