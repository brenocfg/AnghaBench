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
struct TYPE_8__ {int /*<<< orphan*/ * qps; TYPE_2__* indir_qp; } ;
struct mlx4_en_priv {int flags; int rx_ring_num; TYPE_4__* mdev; TYPE_3__ rss_map; scalar_t__ validate_loopback; int /*<<< orphan*/  ctrl_flags; } ;
typedef  int netdev_features_t ;
struct TYPE_6__ {int flags2; } ;
struct TYPE_10__ {TYPE_1__ caps; } ;
struct TYPE_9__ {int /*<<< orphan*/  state_lock; TYPE_5__* dev; } ;
struct TYPE_7__ {scalar_t__ qpn; } ;

/* Variables and functions */
 int MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB ; 
 int MLX4_EN_FLAG_ENABLE_HW_LOOPBACK ; 
 int MLX4_EN_FLAG_RX_FILTER_NEEDED ; 
 int /*<<< orphan*/  MLX4_WQE_CTRL_FORCE_LOOPBACK ; 
 int NETIF_F_LOOPBACK ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int mlx4_en_change_mcast_lb (struct mlx4_en_priv*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mlx4_is_mfunc (TYPE_5__*) ; 
 int /*<<< orphan*/  mlx4_warn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

void mlx4_en_update_loopback_state(struct net_device *dev,
				   netdev_features_t features)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	if (features & NETIF_F_LOOPBACK)
		priv->ctrl_flags |= cpu_to_be32(MLX4_WQE_CTRL_FORCE_LOOPBACK);
	else
		priv->ctrl_flags &= cpu_to_be32(~MLX4_WQE_CTRL_FORCE_LOOPBACK);

	priv->flags &= ~(MLX4_EN_FLAG_RX_FILTER_NEEDED|
			MLX4_EN_FLAG_ENABLE_HW_LOOPBACK);

	/* Drop the packet if SRIOV is not enabled
	 * and not performing the selftest or flb disabled
	 */
	if (mlx4_is_mfunc(priv->mdev->dev) &&
	    !(features & NETIF_F_LOOPBACK) && !priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_RX_FILTER_NEEDED;

	/* Set dmac in Tx WQE if we are in SRIOV mode or if loopback selftest
	 * is requested
	 */
	if (mlx4_is_mfunc(priv->mdev->dev) || priv->validate_loopback)
		priv->flags |= MLX4_EN_FLAG_ENABLE_HW_LOOPBACK;

	mutex_lock(&priv->mdev->state_lock);
	if ((priv->mdev->dev->caps.flags2 &
	     MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB) &&
	    priv->rss_map.indir_qp && priv->rss_map.indir_qp->qpn) {
		int i;
		int err = 0;
		int loopback = !!(features & NETIF_F_LOOPBACK);

		for (i = 0; i < priv->rx_ring_num; i++) {
			int ret;

			ret = mlx4_en_change_mcast_lb(priv,
						      &priv->rss_map.qps[i],
						      loopback);
			if (!err)
				err = ret;
		}
		if (err)
			mlx4_warn(priv->mdev, "failed to change mcast loopback\n");
	}
	mutex_unlock(&priv->mdev->state_lock);
}