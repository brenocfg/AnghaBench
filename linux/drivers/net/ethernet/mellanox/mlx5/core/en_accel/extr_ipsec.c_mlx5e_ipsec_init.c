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
struct mlx5e_priv {TYPE_1__* netdev; int /*<<< orphan*/  mdev; struct mlx5e_ipsec* ipsec; } ;
struct mlx5e_ipsec {int no_trailer; int /*<<< orphan*/  wq; struct mlx5e_priv* en_priv; int /*<<< orphan*/  halloc; int /*<<< orphan*/  sadb_rx_lock; int /*<<< orphan*/  sadb_rx; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER ; 
 int /*<<< orphan*/  MLX5_IPSEC_DEV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mlx5e_ipsec*) ; 
 struct mlx5e_ipsec* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_accel_ipsec_device_caps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5e_ipsec_init(struct mlx5e_priv *priv)
{
	struct mlx5e_ipsec *ipsec = NULL;

	if (!MLX5_IPSEC_DEV(priv->mdev)) {
		netdev_dbg(priv->netdev, "Not an IPSec offload device\n");
		return 0;
	}

	ipsec = kzalloc(sizeof(*ipsec), GFP_KERNEL);
	if (!ipsec)
		return -ENOMEM;

	hash_init(ipsec->sadb_rx);
	spin_lock_init(&ipsec->sadb_rx_lock);
	ida_init(&ipsec->halloc);
	ipsec->en_priv = priv;
	ipsec->en_priv->ipsec = ipsec;
	ipsec->no_trailer = !!(mlx5_accel_ipsec_device_caps(priv->mdev) &
			       MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER);
	ipsec->wq = alloc_ordered_workqueue("mlx5e_ipsec: %s", 0,
					    priv->netdev->name);
	if (!ipsec->wq) {
		kfree(ipsec);
		return -ENOMEM;
	}
	netdev_dbg(priv->netdev, "IPSec attached to netdevice\n");
	return 0;
}