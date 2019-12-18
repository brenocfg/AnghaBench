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
typedef  scalar_t__ u16 ;
struct vnic_rq_buf {int /*<<< orphan*/  dma_addr; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct enic {scalar_t__ rx_copybreak; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 struct enic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool enic_rxcopybreak(struct net_device *netdev, struct sk_buff **skb,
			     struct vnic_rq_buf *buf, u16 len)
{
	struct enic *enic = netdev_priv(netdev);
	struct sk_buff *new_skb;

	if (len > enic->rx_copybreak)
		return false;
	new_skb = netdev_alloc_skb_ip_align(netdev, len);
	if (!new_skb)
		return false;
	pci_dma_sync_single_for_cpu(enic->pdev, buf->dma_addr, len,
				    DMA_FROM_DEVICE);
	memcpy(new_skb->data, (*skb)->data, len);
	*skb = new_skb;

	return true;
}