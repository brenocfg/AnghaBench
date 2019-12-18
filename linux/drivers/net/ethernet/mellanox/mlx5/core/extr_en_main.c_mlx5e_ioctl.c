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
struct mlx5e_priv {int dummy; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGHWTSTAMP 129 
#define  SIOCSHWTSTAMP 128 
 int mlx5e_hwstamp_get (struct mlx5e_priv*,struct ifreq*) ; 
 int mlx5e_hwstamp_set (struct mlx5e_priv*,struct ifreq*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx5e_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	switch (cmd) {
	case SIOCSHWTSTAMP:
		return mlx5e_hwstamp_set(priv, ifr);
	case SIOCGHWTSTAMP:
		return mlx5e_hwstamp_get(priv, ifr);
	default:
		return -EOPNOTSUPP;
	}
}