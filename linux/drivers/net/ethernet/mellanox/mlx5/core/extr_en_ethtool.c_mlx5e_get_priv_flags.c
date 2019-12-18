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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pflags; } ;
struct TYPE_4__ {TYPE_1__ params; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;

/* Variables and functions */
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 mlx5e_get_priv_flags(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	return priv->channels.params.pflags;
}