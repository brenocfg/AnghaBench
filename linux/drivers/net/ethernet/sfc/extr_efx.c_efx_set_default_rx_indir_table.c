#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct efx_rss_context {int /*<<< orphan*/ * rx_indir_table; } ;
struct efx_nic {int /*<<< orphan*/  rss_spread; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ethtool_rxfh_indir_default (size_t,int /*<<< orphan*/ ) ; 

void efx_set_default_rx_indir_table(struct efx_nic *efx,
				    struct efx_rss_context *ctx)
{
	size_t i;

	for (i = 0; i < ARRAY_SIZE(ctx->rx_indir_table); i++)
		ctx->rx_indir_table[i] =
			ethtool_rxfh_indir_default(i, efx->rss_spread);
}