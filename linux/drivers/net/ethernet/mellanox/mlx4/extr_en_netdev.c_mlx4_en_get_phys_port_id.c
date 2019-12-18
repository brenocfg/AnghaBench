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
typedef  int u64 ;
struct netdev_phys_item_id {int id_len; int* id; } ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {size_t port; TYPE_1__* mdev; } ;
struct TYPE_4__ {int* phys_port_id; } ;
struct mlx4_dev {TYPE_2__ caps; } ;
typedef  int /*<<< orphan*/  phys_port_id ;
struct TYPE_3__ {struct mlx4_dev* dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int PORT_ID_BYTE_LEN ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int mlx4_en_get_phys_port_id(struct net_device *dev,
				    struct netdev_phys_item_id *ppid)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_dev *mdev = priv->mdev->dev;
	int i;
	u64 phys_port_id = mdev->caps.phys_port_id[priv->port];

	if (!phys_port_id)
		return -EOPNOTSUPP;

	ppid->id_len = sizeof(phys_port_id);
	for (i = PORT_ID_BYTE_LEN - 1; i >= 0; --i) {
		ppid->id[i] =  phys_port_id & 0xff;
		phys_port_id >>= 8;
	}
	return 0;
}