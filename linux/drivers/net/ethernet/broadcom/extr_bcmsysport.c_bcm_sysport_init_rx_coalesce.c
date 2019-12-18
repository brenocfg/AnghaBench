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
typedef  int /*<<< orphan*/  u32 ;
struct dim_cq_moder {int /*<<< orphan*/  pkts; int /*<<< orphan*/  usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct bcm_sysport_net_dim {TYPE_1__ dim; scalar_t__ use_dim; } ;
struct bcm_sysport_priv {int /*<<< orphan*/  rx_max_coalesced_frames; int /*<<< orphan*/  rx_coalesce_usecs; struct bcm_sysport_net_dim dim; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_sysport_set_rx_coalesce (struct bcm_sysport_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dim_cq_moder net_dim_get_def_rx_moderation (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sysport_init_rx_coalesce(struct bcm_sysport_priv *priv)
{
	struct bcm_sysport_net_dim *dim = &priv->dim;
	struct dim_cq_moder moder;
	u32 usecs, pkts;

	usecs = priv->rx_coalesce_usecs;
	pkts = priv->rx_max_coalesced_frames;

	/* If DIM was enabled, re-apply default parameters */
	if (dim->use_dim) {
		moder = net_dim_get_def_rx_moderation(dim->dim.mode);
		usecs = moder.usec;
		pkts = moder.pkts;
	}

	bcm_sysport_set_rx_coalesce(priv, usecs, pkts);
}