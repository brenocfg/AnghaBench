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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dcb_pfc; } ;
struct mlx4_en_priv {TYPE_1__ cee_config; } ;

/* Variables and functions */
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_dcbnl_get_pfc_cfg(struct net_device *netdev, int priority,
				      u8 *setting)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);

	*setting = priv->cee_config.dcb_pfc[priority];
}