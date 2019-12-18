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
struct rdma_netdev {int /*<<< orphan*/  set_id; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  send; struct ib_device* hca; } ;
struct net_device {int needs_free_netdev; int /*<<< orphan*/  priv_destructor; } ;
struct mlx5i_priv {scalar_t__ sub_interface; struct rdma_netdev rn; } ;
struct mlx5e_profile {int /*<<< orphan*/  (* cleanup ) (struct mlx5e_priv*) ;int /*<<< orphan*/  (* init ) (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,struct mlx5i_priv*) ;} ;
struct mlx5e_priv {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 struct mlx5e_profile* mlx5_get_profile (struct mlx5_core_dev*) ; 
 scalar_t__ mlx5_is_sub_interface (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_rdma_netdev_free ; 
 int mlx5e_attach_netdev (struct mlx5e_priv*) ; 
 int mlx5e_create_mdev_resources (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5e_destroy_mdev_resources (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5i_attach_mcast ; 
 int /*<<< orphan*/  mlx5i_detach_mcast ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_pkey_qpn_ht_cleanup (struct net_device*) ; 
 int mlx5i_pkey_qpn_ht_init (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_set_pkey_index ; 
 int /*<<< orphan*/  mlx5i_xmit ; 
 struct mlx5i_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,struct mlx5i_priv*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5e_priv*) ; 

__attribute__((used)) static int mlx5_rdma_setup_rn(struct ib_device *ibdev, u8 port_num,
			      struct net_device *netdev, void *param)
{
	struct mlx5_core_dev *mdev = (struct mlx5_core_dev *)param;
	const struct mlx5e_profile *prof = mlx5_get_profile(mdev);
	struct mlx5i_priv *ipriv;
	struct mlx5e_priv *epriv;
	struct rdma_netdev *rn;
	int err;

	ipriv = netdev_priv(netdev);
	epriv = mlx5i_epriv(netdev);

	ipriv->sub_interface = mlx5_is_sub_interface(mdev);
	if (!ipriv->sub_interface) {
		err = mlx5i_pkey_qpn_ht_init(netdev);
		if (err) {
			mlx5_core_warn(mdev, "allocate qpn_to_netdev ht failed\n");
			return err;
		}

		/* This should only be called once per mdev */
		err = mlx5e_create_mdev_resources(mdev);
		if (err)
			goto destroy_ht;
	}

	prof->init(mdev, netdev, prof, ipriv);

	err = mlx5e_attach_netdev(epriv);
	if (err)
		goto detach;
	netif_carrier_off(netdev);

	/* set rdma_netdev func pointers */
	rn = &ipriv->rn;
	rn->hca  = ibdev;
	rn->send = mlx5i_xmit;
	rn->attach_mcast = mlx5i_attach_mcast;
	rn->detach_mcast = mlx5i_detach_mcast;
	rn->set_id = mlx5i_set_pkey_index;

	netdev->priv_destructor = mlx5_rdma_netdev_free;
	netdev->needs_free_netdev = 1;

	return 0;

detach:
	prof->cleanup(epriv);
	if (ipriv->sub_interface)
		return err;
	mlx5e_destroy_mdev_resources(mdev);
destroy_ht:
	mlx5i_pkey_qpn_ht_cleanup(netdev);
	return err;
}