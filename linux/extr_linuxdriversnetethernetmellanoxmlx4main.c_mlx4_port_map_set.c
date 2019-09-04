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
typedef  int u8 ;
struct TYPE_4__ {int port1; int port2; } ;
struct mlx4_priv {int /*<<< orphan*/  bond_mutex; TYPE_2__ v2p; } ;
struct mlx4_port_map {int port1; int port2; } ;
struct TYPE_3__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MLX4_DEV_CAP_FLAG2_PORT_REMAP ; 
 int MLX4_MAX_PORTS ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int mlx4_virt2phy_port_map (struct mlx4_dev*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx4_port_map_set(struct mlx4_dev *dev, struct mlx4_port_map *v2p)
{
	u8 port1 = v2p->port1;
	u8 port2 = v2p->port2;
	struct mlx4_priv *priv = mlx4_priv(dev);
	int err;

	if (!(dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_PORT_REMAP))
		return -EOPNOTSUPP;

	mutex_lock(&priv->bond_mutex);

	/* zero means keep current mapping for this port */
	if (port1 == 0)
		port1 = priv->v2p.port1;
	if (port2 == 0)
		port2 = priv->v2p.port2;

	if ((port1 < 1) || (port1 > MLX4_MAX_PORTS) ||
	    (port2 < 1) || (port2 > MLX4_MAX_PORTS) ||
	    (port1 == 2 && port2 == 1)) {
		/* besides boundary checks cross mapping makes
		 * no sense and therefore not allowed */
		err = -EINVAL;
	} else if ((port1 == priv->v2p.port1) &&
		 (port2 == priv->v2p.port2)) {
		err = 0;
	} else {
		err = mlx4_virt2phy_port_map(dev, port1, port2);
		if (!err) {
			mlx4_dbg(dev, "port map changed: [%d][%d]\n",
				 port1, port2);
			priv->v2p.port1 = port1;
			priv->v2p.port2 = port2;
		} else {
			mlx4_err(dev, "Failed to change port mape: %d\n", err);
		}
	}

	mutex_unlock(&priv->bond_mutex);
	return err;
}