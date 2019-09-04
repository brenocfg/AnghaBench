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
struct net_device {int dummy; } ;
struct mlx5i_priv {int /*<<< orphan*/  qpn_htbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct mlx5i_priv* netdev_priv (struct net_device*) ; 

void mlx5i_pkey_qpn_ht_cleanup(struct net_device *netdev)
{
	struct mlx5i_priv *ipriv = netdev_priv(netdev);

	kfree(ipriv->qpn_htbl);
}