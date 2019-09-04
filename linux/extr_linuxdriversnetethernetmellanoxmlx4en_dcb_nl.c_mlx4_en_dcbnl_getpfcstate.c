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
struct TYPE_2__ {int /*<<< orphan*/  pfc_state; } ;
struct mlx4_en_priv {TYPE_1__ cee_config; } ;

/* Variables and functions */
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx4_en_dcbnl_getpfcstate(struct net_device *netdev)
{
	struct mlx4_en_priv *priv = netdev_priv(netdev);

	return priv->cee_config.pfc_state;
}