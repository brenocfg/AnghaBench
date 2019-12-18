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
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct mlx5e_params {int dummy; } ;
struct TYPE_3__ {struct mlx5e_channel** c; struct mlx5e_params params; } ;
struct mlx5e_priv {TYPE_1__ channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct mlx5e_channel {int /*<<< orphan*/  xskicosq_lock; TYPE_2__ xskicosq; int /*<<< orphan*/  napi; int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENETDOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  MLX5E_CHANNEL_STATE_XSK ; 
 int /*<<< orphan*/  MLX5E_RQ_GROUP_XSK ; 
 int /*<<< orphan*/  MLX5E_SQ_STATE_ENABLED ; 
 int /*<<< orphan*/  mlx5e_qid_get_ch_if_in_group (struct mlx5e_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  mlx5e_trigger_irq (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5e_xdp_is_open (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  napi_if_scheduled_mark_missed (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int mlx5e_xsk_wakeup(struct net_device *dev, u32 qid, u32 flags)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_params *params = &priv->channels.params;
	struct mlx5e_channel *c;
	u16 ix;

	if (unlikely(!mlx5e_xdp_is_open(priv)))
		return -ENETDOWN;

	if (unlikely(!mlx5e_qid_get_ch_if_in_group(params, qid, MLX5E_RQ_GROUP_XSK, &ix)))
		return -EINVAL;

	c = priv->channels.c[ix];

	if (unlikely(!test_bit(MLX5E_CHANNEL_STATE_XSK, c->state)))
		return -ENXIO;

	if (!napi_if_scheduled_mark_missed(&c->napi)) {
		/* To avoid WQE overrun, don't post a NOP if XSKICOSQ is not
		 * active and not polled by NAPI. Return 0, because the upcoming
		 * activate will trigger the IRQ for us.
		 */
		if (unlikely(!test_bit(MLX5E_SQ_STATE_ENABLED, &c->xskicosq.state)))
			return 0;

		spin_lock(&c->xskicosq_lock);
		mlx5e_trigger_irq(&c->xskicosq);
		spin_unlock(&c->xskicosq_lock);
	}

	return 0;
}