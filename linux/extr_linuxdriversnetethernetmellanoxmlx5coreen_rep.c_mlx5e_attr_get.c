#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; int /*<<< orphan*/  id_len; } ;
struct TYPE_6__ {TYPE_1__ ppid; } ;
struct switchdev_attr {int id; TYPE_2__ u; } ;
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {TYPE_4__* mdev; struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  hw_id; } ;
struct mlx5_eswitch {scalar_t__ mode; } ;
struct TYPE_7__ {struct mlx5_eswitch* eswitch; } ;
struct TYPE_8__ {TYPE_3__ priv; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ SRIOV_NONE ; 
#define  SWITCHDEV_ATTR_ID_PORT_PARENT_ID 128 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

int mlx5e_attr_get(struct net_device *dev, struct switchdev_attr *attr)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct mlx5_eswitch *esw = priv->mdev->priv.eswitch;

	if (esw->mode == SRIOV_NONE)
		return -EOPNOTSUPP;

	switch (attr->id) {
	case SWITCHDEV_ATTR_ID_PORT_PARENT_ID:
		attr->u.ppid.id_len = ETH_ALEN;
		ether_addr_copy(attr->u.ppid.id, rep->hw_id);
		break;
	default:
		return -EOPNOTSUPP;
	}

	return 0;
}