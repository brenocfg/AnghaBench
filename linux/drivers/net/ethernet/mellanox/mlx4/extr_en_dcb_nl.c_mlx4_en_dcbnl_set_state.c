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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int dcbx_cap; int flags; } ;

/* Variables and functions */
 int DCB_CAP_DCBX_VER_CEE ; 
 int IEEE_8021QAZ_MAX_TCS ; 
 int MLX4_EN_FLAG_DCB_ENABLED ; 
 scalar_t__ mlx4_en_alloc_tx_queue_per_tc (struct net_device*,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx4_en_dcbnl_set_state(struct net_device *dev, u8 state)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int num_tcs = 0;

	if (!(priv->dcbx_cap & DCB_CAP_DCBX_VER_CEE))
		return 1;

	if (!!(state) == !!(priv->flags & MLX4_EN_FLAG_DCB_ENABLED))
		return 0;

	if (state) {
		priv->flags |= MLX4_EN_FLAG_DCB_ENABLED;
		num_tcs = IEEE_8021QAZ_MAX_TCS;
	} else {
		priv->flags &= ~MLX4_EN_FLAG_DCB_ENABLED;
	}

	if (mlx4_en_alloc_tx_queue_per_tc(dev, num_tcs))
		return 1;

	return 0;
}