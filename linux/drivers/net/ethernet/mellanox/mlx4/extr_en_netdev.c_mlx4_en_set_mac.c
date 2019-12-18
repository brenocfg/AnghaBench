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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {unsigned char* dev_addr; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx4_en_do_set_mac (struct mlx4_en_priv*,unsigned char*) ; 
 int /*<<< orphan*/  mlx4_en_update_user_mac (struct mlx4_en_priv*,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_mac(struct net_device *dev, void *addr)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct sockaddr *saddr = addr;
	unsigned char new_mac[ETH_ALEN + 2];
	int err;

	if (!is_valid_ether_addr(saddr->sa_data))
		return -EADDRNOTAVAIL;

	mutex_lock(&mdev->state_lock);
	memcpy(new_mac, saddr->sa_data, ETH_ALEN);
	err = mlx4_en_do_set_mac(priv, new_mac);
	if (err)
		goto out;

	memcpy(dev->dev_addr, saddr->sa_data, ETH_ALEN);
	mlx4_en_update_user_mac(priv, new_mac);
out:
	mutex_unlock(&mdev->state_lock);

	return err;
}