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
struct ipw2100_rx {int dummy; } ;
struct ipw2100_priv {TYPE_1__* rx_buffers; int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  rx_queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  skb; int /*<<< orphan*/  dma_addr; scalar_t__ rxp; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*) ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int RX_QUEUE_LENGTH ; 
 int /*<<< orphan*/  bd_queue_free (struct ipw2100_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_queue_free (struct ipw2100_priv*) ; 

__attribute__((used)) static void ipw2100_rx_free(struct ipw2100_priv *priv)
{
	int i;

	IPW_DEBUG_INFO("enter\n");

	bd_queue_free(priv, &priv->rx_queue);
	status_queue_free(priv);

	if (!priv->rx_buffers)
		return;

	for (i = 0; i < RX_QUEUE_LENGTH; i++) {
		if (priv->rx_buffers[i].rxp) {
			pci_unmap_single(priv->pci_dev,
					 priv->rx_buffers[i].dma_addr,
					 sizeof(struct ipw2100_rx),
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(priv->rx_buffers[i].skb);
		}
	}

	kfree(priv->rx_buffers);
	priv->rx_buffers = NULL;

	IPW_DEBUG_INFO("exit\n");
}