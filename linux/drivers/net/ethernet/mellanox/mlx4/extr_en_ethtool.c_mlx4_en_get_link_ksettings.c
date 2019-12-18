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
struct net_device {int dummy; } ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  link_speed; } ;
struct mlx4_en_priv {TYPE_3__ port_state; TYPE_5__* mdev; int /*<<< orphan*/  port; } ;
struct TYPE_9__ {int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct ethtool_link_ksettings {TYPE_4__ base; } ;
struct TYPE_10__ {TYPE_2__* dev; } ;
struct TYPE_6__ {int flags2; } ;
struct TYPE_7__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int EINVAL ; 
 int ENOMEM ; 
 int MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL ; 
 int MLX4_EN_PORT_ANC ; 
 int MLX4_EN_PORT_ANE ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int,int) ; 
 int /*<<< orphan*/  ethtool_get_default_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 int ethtool_get_ptys_link_ksettings (struct net_device*,struct ethtool_link_ksettings*) ; 
 scalar_t__ mlx4_en_QUERY_PORT (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 

__attribute__((used)) static int
mlx4_en_get_link_ksettings(struct net_device *dev,
			   struct ethtool_link_ksettings *link_ksettings)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int ret = -EINVAL;

	if (mlx4_en_QUERY_PORT(priv->mdev, priv->port))
		return -ENOMEM;

	en_dbg(DRV, priv, "query port state.flags ANC(%x) ANE(%x)\n",
	       priv->port_state.flags & MLX4_EN_PORT_ANC,
	       priv->port_state.flags & MLX4_EN_PORT_ANE);

	if (priv->mdev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_ETH_PROT_CTRL)
		ret = ethtool_get_ptys_link_ksettings(dev, link_ksettings);
	if (ret) /* ETH PROT CRTL is not supported or PTYS CMD failed */
		ethtool_get_default_link_ksettings(dev, link_ksettings);

	if (netif_carrier_ok(dev)) {
		link_ksettings->base.speed = priv->port_state.link_speed;
		link_ksettings->base.duplex = DUPLEX_FULL;
	} else {
		link_ksettings->base.speed = SPEED_UNKNOWN;
		link_ksettings->base.duplex = DUPLEX_UNKNOWN;
	}
	return 0;
}