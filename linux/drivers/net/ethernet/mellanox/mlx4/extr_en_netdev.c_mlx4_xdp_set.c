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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx4_en_priv {int rx_ring_num; int* tx_ring_num; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  port; TYPE_1__** rx_ring; scalar_t__ port_up; TYPE_2__* prof; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_port_profile {int* tx_ring_num; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  workqueue; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_up; } ;
struct TYPE_3__ {int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 int ALIGN (int,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int MAX_TX_RINGS ; 
 int PTR_ERR (struct bpf_prog*) ; 
 size_t TX ; 
 size_t TX_XDP ; 
 struct bpf_prog* bpf_prog_add (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_sub (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  en_warn (struct mlx4_en_priv*,char*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_priv*) ; 
 struct mlx4_en_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct mlx4_en_port_profile*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mlx4_en_check_xdp_mtu (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_safe_replace_resources (struct mlx4_en_priv*,struct mlx4_en_priv*) ; 
 int mlx4_en_start_port (struct net_device*) ; 
 int /*<<< orphan*/  mlx4_en_stop_port (struct net_device*,int) ; 
 int mlx4_en_try_alloc_resources (struct mlx4_en_priv*,struct mlx4_en_priv*,struct mlx4_en_port_profile*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_set_real_num_tx_queues (struct net_device*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct bpf_prog*) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_xdp_set(struct net_device *dev, struct bpf_prog *prog)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_port_profile new_prof;
	struct bpf_prog *old_prog;
	struct mlx4_en_priv *tmp;
	int tx_changed = 0;
	int xdp_ring_num;
	int port_up = 0;
	int err;
	int i;

	xdp_ring_num = prog ? priv->rx_ring_num : 0;

	/* No need to reconfigure buffers when simply swapping the
	 * program for a new one.
	 */
	if (priv->tx_ring_num[TX_XDP] == xdp_ring_num) {
		if (prog) {
			prog = bpf_prog_add(prog, priv->rx_ring_num - 1);
			if (IS_ERR(prog))
				return PTR_ERR(prog);
		}
		mutex_lock(&mdev->state_lock);
		for (i = 0; i < priv->rx_ring_num; i++) {
			old_prog = rcu_dereference_protected(
					priv->rx_ring[i]->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
			rcu_assign_pointer(priv->rx_ring[i]->xdp_prog, prog);
			if (old_prog)
				bpf_prog_put(old_prog);
		}
		mutex_unlock(&mdev->state_lock);
		return 0;
	}

	if (!mlx4_en_check_xdp_mtu(dev, dev->mtu))
		return -EOPNOTSUPP;

	tmp = kzalloc(sizeof(*tmp), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;

	if (prog) {
		prog = bpf_prog_add(prog, priv->rx_ring_num - 1);
		if (IS_ERR(prog)) {
			err = PTR_ERR(prog);
			goto out;
		}
	}

	mutex_lock(&mdev->state_lock);
	memcpy(&new_prof, priv->prof, sizeof(struct mlx4_en_port_profile));
	new_prof.tx_ring_num[TX_XDP] = xdp_ring_num;

	if (priv->tx_ring_num[TX] + xdp_ring_num > MAX_TX_RINGS) {
		tx_changed = 1;
		new_prof.tx_ring_num[TX] =
			MAX_TX_RINGS - ALIGN(xdp_ring_num, priv->prof->num_up);
		en_warn(priv, "Reducing the number of TX rings, to not exceed the max total rings number.\n");
	}

	err = mlx4_en_try_alloc_resources(priv, tmp, &new_prof, false);
	if (err) {
		if (prog)
			bpf_prog_sub(prog, priv->rx_ring_num - 1);
		goto unlock_out;
	}

	if (priv->port_up) {
		port_up = 1;
		mlx4_en_stop_port(dev, 1);
	}

	mlx4_en_safe_replace_resources(priv, tmp);
	if (tx_changed)
		netif_set_real_num_tx_queues(dev, priv->tx_ring_num[TX]);

	for (i = 0; i < priv->rx_ring_num; i++) {
		old_prog = rcu_dereference_protected(
					priv->rx_ring[i]->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
		rcu_assign_pointer(priv->rx_ring[i]->xdp_prog, prog);
		if (old_prog)
			bpf_prog_put(old_prog);
	}

	if (port_up) {
		err = mlx4_en_start_port(dev);
		if (err) {
			en_err(priv, "Failed starting port %d for XDP change\n",
			       priv->port);
			queue_work(mdev->workqueue, &priv->watchdog_task);
		}
	}

unlock_out:
	mutex_unlock(&mdev->state_lock);
out:
	kfree(tmp);
	return err;
}