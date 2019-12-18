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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CEE_STATE_DOWN ; 
 int /*<<< orphan*/  MLX4_CEE_STATE_UP ; 
 int MLX4_EN_FLAG_DCB_ENABLED ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx4_en_dcbnl_get_state(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	if (priv->flags & MLX4_EN_FLAG_DCB_ENABLED)
		return MLX4_CEE_STATE_UP;

	return MLX4_CEE_STATE_DOWN;
}