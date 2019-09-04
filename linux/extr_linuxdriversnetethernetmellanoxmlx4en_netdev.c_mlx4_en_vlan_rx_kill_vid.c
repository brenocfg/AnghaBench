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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {scalar_t__ port_up; int /*<<< orphan*/  port; int /*<<< orphan*/  active_vlans; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  dev; scalar_t__ device_up; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  HW ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*) ; 
 int mlx4_SET_VLAN_FLTR (int /*<<< orphan*/ ,struct mlx4_en_priv*) ; 
 int /*<<< orphan*/  mlx4_unregister_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_vlan_rx_kill_vid(struct net_device *dev,
				    __be16 proto, u16 vid)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	int err = 0;

	en_dbg(HW, priv, "Killing VID:%d\n", vid);

	clear_bit(vid, priv->active_vlans);

	/* Remove VID from port VLAN filter */
	mutex_lock(&mdev->state_lock);
	mlx4_unregister_vlan(mdev->dev, priv->port, vid);

	if (mdev->device_up && priv->port_up) {
		err = mlx4_SET_VLAN_FLTR(mdev->dev, priv);
		if (err)
			en_err(priv, "Failed configuring VLAN filter\n");
	}
	mutex_unlock(&mdev->state_lock);

	return err;
}