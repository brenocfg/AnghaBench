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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {struct bpf_prog* xdp_prog; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; TYPE_2__ channels; } ;
struct bpf_prog {TYPE_3__* aux; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 mlx5e_xdp_query(struct net_device *dev)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	const struct bpf_prog *xdp_prog;
	u32 prog_id = 0;

	mutex_lock(&priv->state_lock);
	xdp_prog = priv->channels.params.xdp_prog;
	if (xdp_prog)
		prog_id = xdp_prog->aux->id;
	mutex_unlock(&priv->state_lock);

	return prog_id;
}