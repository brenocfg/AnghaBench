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
struct net_device {int /*<<< orphan*/  dev; } ;
struct grcan_dma {int /*<<< orphan*/  base_handle; int /*<<< orphan*/  base_buf; int /*<<< orphan*/  base_size; } ;
struct grcan_priv {struct grcan_dma dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct grcan_dma*,int /*<<< orphan*/ ,int) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void grcan_free_dma_buffers(struct net_device *dev)
{
	struct grcan_priv *priv = netdev_priv(dev);
	struct grcan_dma *dma = &priv->dma;

	dma_free_coherent(&dev->dev, dma->base_size, dma->base_buf,
			  dma->base_handle);
	memset(dma, 0, sizeof(*dma));
}