#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_4__ {int num; struct mlx5e_channel** c; TYPE_3__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_1__ channels; int /*<<< orphan*/  state; int /*<<< orphan*/  mdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  state; int /*<<< orphan*/  xdp_prog; } ;
struct mlx5e_channel {int /*<<< orphan*/  napi; TYPE_2__ rq; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  MLX5E_RQ_STATE_ENABLED ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int PTR_ERR (struct bpf_prog*) ; 
 struct bpf_prog* bpf_prog_add (struct bpf_prog*,int) ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_locked (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_open_locked (struct net_device*) ; 
 int /*<<< orphan*/  mlx5e_set_rq_type (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int mlx5e_xdp_allowed (struct mlx5e_priv*,struct bpf_prog*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bpf_prog* xchg (int /*<<< orphan*/ *,struct bpf_prog*) ; 

__attribute__((used)) static int mlx5e_xdp_set(struct net_device *netdev, struct bpf_prog *prog)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct bpf_prog *old_prog;
	bool reset, was_opened;
	int err = 0;
	int i;

	mutex_lock(&priv->state_lock);

	if (prog) {
		err = mlx5e_xdp_allowed(priv, prog);
		if (err)
			goto unlock;
	}

	was_opened = test_bit(MLX5E_STATE_OPENED, &priv->state);
	/* no need for full reset when exchanging programs */
	reset = (!priv->channels.params.xdp_prog || !prog);

	if (was_opened && reset)
		mlx5e_close_locked(netdev);
	if (was_opened && !reset) {
		/* num_channels is invariant here, so we can take the
		 * batched reference right upfront.
		 */
		prog = bpf_prog_add(prog, priv->channels.num);
		if (IS_ERR(prog)) {
			err = PTR_ERR(prog);
			goto unlock;
		}
	}

	/* exchange programs, extra prog reference we got from caller
	 * as long as we don't fail from this point onwards.
	 */
	old_prog = xchg(&priv->channels.params.xdp_prog, prog);
	if (old_prog)
		bpf_prog_put(old_prog);

	if (reset) /* change RQ type according to priv->xdp_prog */
		mlx5e_set_rq_type(priv->mdev, &priv->channels.params);

	if (was_opened && reset)
		mlx5e_open_locked(netdev);

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state) || reset)
		goto unlock;

	/* exchanging programs w/o reset, we update ref counts on behalf
	 * of the channels RQs here.
	 */
	for (i = 0; i < priv->channels.num; i++) {
		struct mlx5e_channel *c = priv->channels.c[i];

		clear_bit(MLX5E_RQ_STATE_ENABLED, &c->rq.state);
		napi_synchronize(&c->napi);
		/* prevent mlx5e_poll_rx_cq from accessing rq->xdp_prog */

		old_prog = xchg(&c->rq.xdp_prog, prog);

		set_bit(MLX5E_RQ_STATE_ENABLED, &c->rq.state);
		/* napi_schedule in case we have missed anything */
		napi_schedule(&c->napi);

		if (old_prog)
			bpf_prog_put(old_prog);
	}

unlock:
	mutex_unlock(&priv->state_lock);
	return err;
}