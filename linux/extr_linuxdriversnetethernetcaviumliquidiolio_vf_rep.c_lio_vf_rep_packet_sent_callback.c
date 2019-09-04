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
struct sk_buff {struct net_device* dev; } ;
struct octeon_soft_command {int /*<<< orphan*/  iq_no; int /*<<< orphan*/  datasize; int /*<<< orphan*/  dmadptr; struct sk_buff* ctxptr; } ;
struct octeon_device {TYPE_1__* pci_dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  octeon_free_soft_command (struct octeon_device*,struct octeon_soft_command*) ; 
 scalar_t__ octnet_iq_is_full (struct octeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lio_vf_rep_packet_sent_callback(struct octeon_device *oct,
				u32 status, void *buf)
{
	struct octeon_soft_command *sc = (struct octeon_soft_command *)buf;
	struct sk_buff *skb = sc->ctxptr;
	struct net_device *ndev = skb->dev;
	u32 iq_no;

	dma_unmap_single(&oct->pci_dev->dev, sc->dmadptr,
			 sc->datasize, DMA_TO_DEVICE);
	dev_kfree_skb_any(skb);
	iq_no = sc->iq_no;
	octeon_free_soft_command(oct, sc);

	if (octnet_iq_is_full(oct, iq_no))
		return;

	if (netif_queue_stopped(ndev))
		netif_wake_queue(ndev);
}