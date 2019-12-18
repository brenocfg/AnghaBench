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
struct netdev_phys_item_id {int /*<<< orphan*/  id_len; int /*<<< orphan*/ * id; } ;
struct mlx5e_rep_priv {int /*<<< orphan*/  dl_port; struct mlx5_eswitch_rep* rep; int /*<<< orphan*/  netdev; } ;
struct mlx5_eswitch_rep {unsigned int vport; } ;
struct TYPE_3__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {TYPE_2__* pdev; TYPE_1__ priv; } ;
struct devlink {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVLINK_PORT_FLAVOUR_PHYSICAL ; 
 unsigned int MLX5_VPORT_PF ; 
 unsigned int MLX5_VPORT_UPLINK ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_attrs_pci_pf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_port_attrs_pci_vf_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devlink_port_attrs_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devlink_port_register (struct devlink*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  is_devlink_port_supported (struct mlx5_core_dev*,struct mlx5e_rep_priv*) ; 
 scalar_t__ mlx5_eswitch_is_vf_vport (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mlx5e_rep_get_port_parent_id (int /*<<< orphan*/ ,struct netdev_phys_item_id*) ; 
 struct devlink* priv_to_devlink (struct mlx5_core_dev*) ; 
 unsigned int vport_to_devlink_port_index (struct mlx5_core_dev*,unsigned int) ; 

__attribute__((used)) static int register_devlink_port(struct mlx5_core_dev *dev,
				 struct mlx5e_rep_priv *rpriv)
{
	struct devlink *devlink = priv_to_devlink(dev);
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	struct netdev_phys_item_id ppid = {};
	unsigned int dl_port_index = 0;

	if (!is_devlink_port_supported(dev, rpriv))
		return 0;

	mlx5e_rep_get_port_parent_id(rpriv->netdev, &ppid);

	if (rep->vport == MLX5_VPORT_UPLINK) {
		devlink_port_attrs_set(&rpriv->dl_port,
				       DEVLINK_PORT_FLAVOUR_PHYSICAL,
				       PCI_FUNC(dev->pdev->devfn), false, 0,
				       &ppid.id[0], ppid.id_len);
		dl_port_index = vport_to_devlink_port_index(dev, rep->vport);
	} else if (rep->vport == MLX5_VPORT_PF) {
		devlink_port_attrs_pci_pf_set(&rpriv->dl_port,
					      &ppid.id[0], ppid.id_len,
					      dev->pdev->devfn);
		dl_port_index = rep->vport;
	} else if (mlx5_eswitch_is_vf_vport(dev->priv.eswitch,
					    rpriv->rep->vport)) {
		devlink_port_attrs_pci_vf_set(&rpriv->dl_port,
					      &ppid.id[0], ppid.id_len,
					      dev->pdev->devfn,
					      rep->vport - 1);
		dl_port_index = vport_to_devlink_port_index(dev, rep->vport);
	}

	return devlink_port_register(devlink, &rpriv->dl_port, dl_port_index);
}