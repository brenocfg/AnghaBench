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
struct TYPE_6__ {scalar_t__ refcnt; } ;
struct TYPE_4__ {int num_channels; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
struct mlx5e_priv {int max_nch; int /*<<< orphan*/  state_lock; TYPE_3__ xsk; TYPE_2__ channels; } ;
struct ethtool_channels {int max_combined; int combined_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx5e_ethtool_get_channels(struct mlx5e_priv *priv,
				struct ethtool_channels *ch)
{
	mutex_lock(&priv->state_lock);

	ch->max_combined   = priv->max_nch;
	ch->combined_count = priv->channels.params.num_channels;
	if (priv->xsk.refcnt) {
		/* The upper half are XSK queues. */
		ch->max_combined *= 2;
		ch->combined_count *= 2;
	}

	mutex_unlock(&priv->state_lock);
}