#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx4_ptys_reg {int flags; int /*<<< orphan*/  eth_proto_admin; int /*<<< orphan*/  eth_proto_cap; int /*<<< orphan*/  proto_mask; int /*<<< orphan*/  local_port; } ;
struct mlx4_en_priv {TYPE_4__* mdev; int /*<<< orphan*/  port; scalar_t__ port_up; } ;
struct TYPE_8__ {int speed; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_3__ base; TYPE_1__ link_modes; } ;
typedef  int /*<<< orphan*/  ptys_reg ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_7__ {int flags2; } ;
struct TYPE_10__ {TYPE_2__ caps; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_lock; TYPE_5__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVERTISED ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DRV ; 
 scalar_t__ DUPLEX_HALF ; 
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_1000BASE_CX_SGMII ; 
 int /*<<< orphan*/  MLX4_1000BASE_KX ; 
 int /*<<< orphan*/  MLX4_ACCESS_REG_QUERY ; 
 int /*<<< orphan*/  MLX4_ACCESS_REG_WRITE ; 
 int MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL ; 
 int MLX4_PROT_MASK (int /*<<< orphan*/ ) ; 
 int MLX4_PTYS_AN_DISABLE_ADMIN ; 
 int MLX4_PTYS_AN_DISABLE_CAP ; 
 int /*<<< orphan*/  MLX4_PTYS_EN ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int const,...) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*,...) ; 
 int /*<<< orphan*/  ethtool2ptys_link_modes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx4_ptys_reg*,int /*<<< orphan*/ ,int) ; 
 int mlx4_ACCESS_PTYS_REG (TYPE_5__*,int /*<<< orphan*/ ,struct mlx4_ptys_reg*) ; 
 scalar_t__ mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  speed_set_ptys_admin (struct mlx4_en_priv*,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx4_en_set_link_ksettings(struct net_device *dev,
			   const struct ethtool_link_ksettings *link_ksettings)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_ptys_reg ptys_reg;
	__be32 proto_admin;
	u8 cur_autoneg;
	int ret;

	u32 ptys_adv = ethtool2ptys_link_modes(
		link_ksettings->link_modes.advertising, ADVERTISED);
	const int speed = link_ksettings->base.speed;

	en_dbg(DRV, priv,
	       "Set Speed=%d adv={%*pbl} autoneg=%d duplex=%d\n",
	       speed, __ETHTOOL_LINK_MODE_MASK_NBITS,
	       link_ksettings->link_modes.advertising,
	       link_ksettings->base.autoneg,
	       link_ksettings->base.duplex);

	if (!(priv->mdev->dev->caps.flags2 &
	      MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL) ||
	    (link_ksettings->base.duplex == DUPLEX_HALF))
		return -EINVAL;

	memset(&ptys_reg, 0, sizeof(ptys_reg));
	ptys_reg.local_port = priv->port;
	ptys_reg.proto_mask = MLX4_PTYS_EN;
	ret = mlx4_ACCESS_PTYS_REG(priv->mdev->dev,
				   MLX4_ACCESS_REG_QUERY, &ptys_reg);
	if (ret) {
		en_warn(priv, "Failed to QUERY mlx4_ACCESS_PTYS_REG status(%x)\n",
			ret);
		return 0;
	}

	cur_autoneg = ptys_reg.flags & MLX4_PTYS_AN_DISABLE_ADMIN ?
				AUTONEG_DISABLE : AUTONEG_ENABLE;

	if (link_ksettings->base.autoneg == AUTONEG_DISABLE) {
		proto_admin = speed_set_ptys_admin(priv, speed,
						   ptys_reg.eth_proto_cap);
		if ((be32_to_cpu(proto_admin) &
		     (MLX4_PROT_MASK(MLX4_1000BASE_CX_SGMII) |
		      MLX4_PROT_MASK(MLX4_1000BASE_KX))) &&
		    (ptys_reg.flags & MLX4_PTYS_AN_DISABLE_CAP))
			ptys_reg.flags |= MLX4_PTYS_AN_DISABLE_ADMIN;
	} else {
		proto_admin = cpu_to_be32(ptys_adv);
		ptys_reg.flags &= ~MLX4_PTYS_AN_DISABLE_ADMIN;
	}

	proto_admin &= ptys_reg.eth_proto_cap;
	if (!proto_admin) {
		en_warn(priv, "Not supported link mode(s) requested, check supported link modes.\n");
		return -EINVAL; /* nothing to change due to bad input */
	}

	if ((proto_admin == ptys_reg.eth_proto_admin) &&
	    ((ptys_reg.flags & MLX4_PTYS_AN_DISABLE_CAP) &&
	     (link_ksettings->base.autoneg == cur_autoneg)))
		return 0; /* Nothing to change */

	en_dbg(DRV, priv, "mlx4_ACCESS_PTYS_REG SET: ptys_reg.eth_proto_admin = 0x%x\n",
	       be32_to_cpu(proto_admin));

	ptys_reg.eth_proto_admin = proto_admin;
	ret = mlx4_ACCESS_PTYS_REG(priv->mdev->dev, MLX4_ACCESS_REG_WRITE,
				   &ptys_reg);
	if (ret) {
		en_warn(priv, "Failed to write mlx4_ACCESS_PTYS_REG eth_proto_admin(0x%x) status(0x%x)",
			be32_to_cpu(ptys_reg.eth_proto_admin), ret);
		return ret;
	}

	mutex_lock(&priv->mdev->state_lock);
	if (priv->port_up) {
		en_warn(priv, "Port link mode changed, restarting port...\n");
		mlx4_en_stop_port(dev, 1);
		if (mlx4_en_start_port(dev))
			en_err(priv, "Failed restarting port %d\n", priv->port);
	}
	mutex_unlock(&priv->mdev->state_lock);
	return 0;
}