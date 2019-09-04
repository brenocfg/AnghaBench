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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  port; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int mlx4_set_vf_vlan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_set_vf_vlan(struct net_device *dev, int vf, u16 vlan, u8 qos,
			       __be16 vlan_proto)
{
	struct mlx4_en_priv *en_priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = en_priv->mdev;

	return mlx4_set_vf_vlan(mdev->dev, en_priv->port, vf, vlan, qos,
				vlan_proto);
}