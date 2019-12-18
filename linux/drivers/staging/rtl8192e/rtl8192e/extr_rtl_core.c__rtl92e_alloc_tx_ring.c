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
typedef  scalar_t__ u32 ;
struct tx_desc {scalar_t__ NextDescAddress; } ;
struct r8192_priv {TYPE_1__* tx_ring; int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_2__ {unsigned int entries; int /*<<< orphan*/  queue; scalar_t__ idx; scalar_t__ dma; struct tx_desc* desc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,unsigned int) ; 
 struct tx_desc* pci_zalloc_consistent (int /*<<< orphan*/ ,int,scalar_t__*) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _rtl92e_alloc_tx_ring(struct net_device *dev, unsigned int prio,
				 unsigned int entries)
{
	struct r8192_priv *priv = rtllib_priv(dev);
	struct tx_desc *ring;
	dma_addr_t dma;
	int i;

	ring = pci_zalloc_consistent(priv->pdev, sizeof(*ring) * entries, &dma);
	if (!ring || (unsigned long)ring & 0xFF) {
		netdev_warn(dev, "Cannot allocate TX ring (prio = %d)\n", prio);
		return -ENOMEM;
	}

	priv->tx_ring[prio].desc = ring;
	priv->tx_ring[prio].dma = dma;
	priv->tx_ring[prio].idx = 0;
	priv->tx_ring[prio].entries = entries;
	skb_queue_head_init(&priv->tx_ring[prio].queue);

	for (i = 0; i < entries; i++)
		ring[i].NextDescAddress =
			(u32)dma + ((i + 1) % entries) *
			sizeof(*ring);

	return 0;
}