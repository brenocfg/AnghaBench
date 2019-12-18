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
struct dpaa2_eth_priv {int num_channels; TYPE_1__** channel; } ;
struct TYPE_2__ {scalar_t__ buf_count; } ;

/* Variables and functions */
 int DPAA2_ETH_BUFS_PER_CMD ; 
 int /*<<< orphan*/  drain_bufs (struct dpaa2_eth_priv*,int) ; 

__attribute__((used)) static void drain_pool(struct dpaa2_eth_priv *priv)
{
	int i;

	drain_bufs(priv, DPAA2_ETH_BUFS_PER_CMD);
	drain_bufs(priv, 1);

	for (i = 0; i < priv->num_channels; i++)
		priv->channel[i]->buf_count = 0;
}