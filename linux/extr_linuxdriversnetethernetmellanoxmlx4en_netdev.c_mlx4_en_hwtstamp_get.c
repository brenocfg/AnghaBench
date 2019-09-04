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
struct mlx4_en_priv {int /*<<< orphan*/  hwtstamp_config; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_hwtstamp_get(struct net_device *dev, struct ifreq *ifr)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	return copy_to_user(ifr->ifr_data, &priv->hwtstamp_config,
			    sizeof(priv->hwtstamp_config)) ? -EFAULT : 0;
}