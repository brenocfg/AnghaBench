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
struct dpaa2_eth_priv {int num_channels; struct dpaa2_eth_channel** channel; } ;
struct dpaa2_eth_channel {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disable_ch_napi(struct dpaa2_eth_priv *priv)
{
	struct dpaa2_eth_channel *ch;
	int i;

	for (i = 0; i < priv->num_channels; i++) {
		ch = priv->channel[i];
		napi_disable(&ch->napi);
	}
}