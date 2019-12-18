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
struct TYPE_3__ {scalar_t__ xdp_prog; } ;
struct mlx5e_channels {int num; struct mlx5e_channel** c; TYPE_1__ params; } ;
struct mlx5e_priv {struct mlx5e_channels channels; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct mlx5e_channel {TYPE_2__ rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_STATE_NO_CSUM_COMPLETE ; 
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_pflag_rx_no_csum_complete(struct net_device *netdev, bool enable)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_channels *channels = &priv->channels;
	struct mlx5e_channel *c;
	int i;

	if (!test_bit(MLX5E_STATE_OPENED, &priv->state) ||
	    priv->channels.params.xdp_prog)
		return 0;

	for (i = 0; i < channels->num; i++) {
		c = channels->c[i];
		if (enable)
			__set_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &c->rq.state);
		else
			__clear_bit(MLX5E_RQ_STATE_NO_CSUM_COMPLETE, &c->rq.state);
	}

	return 0;
}