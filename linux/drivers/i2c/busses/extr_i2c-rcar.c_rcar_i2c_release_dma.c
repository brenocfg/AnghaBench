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
struct rcar_i2c_priv {void* dma_rx; void* dma_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 int /*<<< orphan*/  dma_release_channel (void*) ; 

__attribute__((used)) static void rcar_i2c_release_dma(struct rcar_i2c_priv *priv)
{
	if (!IS_ERR(priv->dma_tx)) {
		dma_release_channel(priv->dma_tx);
		priv->dma_tx = ERR_PTR(-EPROBE_DEFER);
	}

	if (!IS_ERR(priv->dma_rx)) {
		dma_release_channel(priv->dma_rx);
		priv->dma_rx = ERR_PTR(-EPROBE_DEFER);
	}
}