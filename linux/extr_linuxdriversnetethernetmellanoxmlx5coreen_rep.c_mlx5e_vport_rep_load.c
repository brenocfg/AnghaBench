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
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {struct net_device* netdev; int /*<<< orphan*/  vport_sqs_list; struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {int dummy; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; TYPE_1__* rep_if; } ;
struct TYPE_4__ {int /*<<< orphan*/  eswitch; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_3__ {struct mlx5e_rep_priv* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 size_t REP_ETH ; 
 int /*<<< orphan*/  kfree (struct mlx5e_rep_priv*) ; 
 struct mlx5e_rep_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mlx5e_rep_priv* mlx5_eswitch_get_uplink_priv (int /*<<< orphan*/ ,size_t) ; 
 int mlx5e_attach_netdev (struct mlx5e_priv*) ; 
 struct net_device* mlx5e_create_netdev (struct mlx5_core_dev*,int /*<<< orphan*/ *,struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5e_destroy_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_detach_netdev (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_cleanup (struct mlx5e_rep_priv*) ; 
 int mlx5e_rep_neigh_init (struct mlx5e_rep_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_profile ; 
 int /*<<< orphan*/  mlx5e_rep_setup_tc_cb_egdev ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int tc_setup_cb_egdev_register (struct net_device*,int /*<<< orphan*/ ,struct mlx5e_priv*) ; 
 int /*<<< orphan*/  tc_setup_cb_egdev_unregister (struct net_device*,int /*<<< orphan*/ ,struct mlx5e_priv*) ; 

__attribute__((used)) static int
mlx5e_vport_rep_load(struct mlx5_core_dev *dev, struct mlx5_eswitch_rep *rep)
{
	struct mlx5e_rep_priv *uplink_rpriv;
	struct mlx5e_rep_priv *rpriv;
	struct net_device *netdev;
	struct mlx5e_priv *upriv;
	int err;

	rpriv = kzalloc(sizeof(*rpriv), GFP_KERNEL);
	if (!rpriv)
		return -ENOMEM;

	netdev = mlx5e_create_netdev(dev, &mlx5e_rep_profile, rpriv);
	if (!netdev) {
		pr_warn("Failed to create representor netdev for vport %d\n",
			rep->vport);
		kfree(rpriv);
		return -EINVAL;
	}

	rpriv->netdev = netdev;
	rpriv->rep = rep;
	rep->rep_if[REP_ETH].priv = rpriv;
	INIT_LIST_HEAD(&rpriv->vport_sqs_list);

	err = mlx5e_attach_netdev(netdev_priv(netdev));
	if (err) {
		pr_warn("Failed to attach representor netdev for vport %d\n",
			rep->vport);
		goto err_destroy_netdev;
	}

	err = mlx5e_rep_neigh_init(rpriv);
	if (err) {
		pr_warn("Failed to initialized neighbours handling for vport %d\n",
			rep->vport);
		goto err_detach_netdev;
	}

	uplink_rpriv = mlx5_eswitch_get_uplink_priv(dev->priv.eswitch, REP_ETH);
	upriv = netdev_priv(uplink_rpriv->netdev);
	err = tc_setup_cb_egdev_register(netdev, mlx5e_rep_setup_tc_cb_egdev,
					 upriv);
	if (err)
		goto err_neigh_cleanup;

	err = register_netdev(netdev);
	if (err) {
		pr_warn("Failed to register representor netdev for vport %d\n",
			rep->vport);
		goto err_egdev_cleanup;
	}

	return 0;

err_egdev_cleanup:
	tc_setup_cb_egdev_unregister(netdev, mlx5e_rep_setup_tc_cb_egdev,
				     upriv);

err_neigh_cleanup:
	mlx5e_rep_neigh_cleanup(rpriv);

err_detach_netdev:
	mlx5e_detach_netdev(netdev_priv(netdev));

err_destroy_netdev:
	mlx5e_destroy_netdev(netdev_priv(netdev));
	kfree(rpriv);
	return err;
}