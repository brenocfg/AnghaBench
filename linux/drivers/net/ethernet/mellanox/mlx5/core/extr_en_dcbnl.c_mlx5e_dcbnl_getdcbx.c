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
struct TYPE_2__ {int /*<<< orphan*/  cap; } ;
struct mlx5e_priv {TYPE_1__ dcbx; } ;

/* Variables and functions */
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u8 mlx5e_dcbnl_getdcbx(struct net_device *dev)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	return priv->dcbx.cap;
}