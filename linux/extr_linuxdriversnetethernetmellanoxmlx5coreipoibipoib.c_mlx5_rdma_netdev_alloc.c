#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rdma_netdev {int /*<<< orphan*/  set_id; int /*<<< orphan*/  detach_mcast; int /*<<< orphan*/  attach_mcast; int /*<<< orphan*/  send; struct ib_device* hca; } ;
struct net_device {int needs_free_netdev; int /*<<< orphan*/  priv_destructor; } ;
struct mlx5i_priv {int sub_interface; struct rdma_netdev rn; } ;
struct mlx5e_profile {int (* max_nch ) (struct mlx5_core_dev*) ;int /*<<< orphan*/  (* init ) (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,struct mlx5i_priv*) ;} ;
struct mlx5e_priv {int /*<<< orphan*/  wq; } ;
struct TYPE_2__ {scalar_t__ pdn; } ;
struct mlx5_core_dev {TYPE_1__ mlx5e_res; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct net_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int MLX5E_MAX_NUM_TC ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev_mqs (int,char const*,int /*<<< orphan*/ ,void (*) (struct net_device*),int,int) ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_rdma_netdev_free ; 
 int /*<<< orphan*/  mlx5e_attach_netdev (struct mlx5e_priv*) ; 
 int mlx5e_create_mdev_resources (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5i_attach_mcast ; 
 scalar_t__ mlx5i_check_required_hca_cap (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5i_detach_mcast ; 
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 struct mlx5e_profile mlx5i_nic_profile ; 
 struct mlx5e_profile* mlx5i_pkey_get_profile () ; 
 int /*<<< orphan*/  mlx5i_pkey_qpn_ht_cleanup (struct net_device*) ; 
 int mlx5i_pkey_qpn_ht_init (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_set_pkey_index ; 
 int /*<<< orphan*/  mlx5i_xmit ; 
 struct mlx5i_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int stub1 (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5_core_dev*,struct net_device*,struct mlx5e_profile const*,struct mlx5i_priv*) ; 

struct net_device *mlx5_rdma_netdev_alloc(struct mlx5_core_dev *mdev,
					  struct ib_device *ibdev,
					  const char *name,
					  void (*setup)(struct net_device *))
{
	const struct mlx5e_profile *profile;
	struct net_device *netdev;
	struct mlx5i_priv *ipriv;
	struct mlx5e_priv *epriv;
	struct rdma_netdev *rn;
	bool sub_interface;
	int nch;
	int err;

	if (mlx5i_check_required_hca_cap(mdev)) {
		mlx5_core_warn(mdev, "Accelerated mode is not supported\n");
		return ERR_PTR(-EOPNOTSUPP);
	}

	/* TODO: Need to find a better way to check if child device*/
	sub_interface = (mdev->mlx5e_res.pdn != 0);

	if (sub_interface)
		profile = mlx5i_pkey_get_profile();
	else
		profile = &mlx5i_nic_profile;

	nch = profile->max_nch(mdev);

	netdev = alloc_netdev_mqs(sizeof(struct mlx5i_priv) + sizeof(struct mlx5e_priv),
				  name, NET_NAME_UNKNOWN,
				  setup,
				  nch * MLX5E_MAX_NUM_TC,
				  nch);
	if (!netdev) {
		mlx5_core_warn(mdev, "alloc_netdev_mqs failed\n");
		return NULL;
	}

	ipriv = netdev_priv(netdev);
	epriv = mlx5i_epriv(netdev);

	epriv->wq = create_singlethread_workqueue("mlx5i");
	if (!epriv->wq)
		goto err_free_netdev;

	ipriv->sub_interface = sub_interface;
	if (!ipriv->sub_interface) {
		err = mlx5i_pkey_qpn_ht_init(netdev);
		if (err) {
			mlx5_core_warn(mdev, "allocate qpn_to_netdev ht failed\n");
			goto destroy_wq;
		}

		/* This should only be called once per mdev */
		err = mlx5e_create_mdev_resources(mdev);
		if (err)
			goto destroy_ht;
	}

	profile->init(mdev, netdev, profile, ipriv);

	mlx5e_attach_netdev(epriv);
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

	return netdev;

destroy_ht:
	mlx5i_pkey_qpn_ht_cleanup(netdev);
destroy_wq:
	destroy_workqueue(epriv->wq);
err_free_netdev:
	free_netdev(netdev);

	return NULL;
}