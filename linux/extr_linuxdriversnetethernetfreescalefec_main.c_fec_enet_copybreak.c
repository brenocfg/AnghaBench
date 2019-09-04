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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {scalar_t__ rx_copybreak; scalar_t__ rx_align; TYPE_1__* pdev; } ;
struct bufdesc {int /*<<< orphan*/  cbd_bufaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ FEC_ENET_RX_FRSIZE ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fec32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  swap_buffer2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool fec_enet_copybreak(struct net_device *ndev, struct sk_buff **skb,
			       struct bufdesc *bdp, u32 length, bool swap)
{
	struct  fec_enet_private *fep = netdev_priv(ndev);
	struct sk_buff *new_skb;

	if (length > fep->rx_copybreak)
		return false;

	new_skb = netdev_alloc_skb(ndev, length);
	if (!new_skb)
		return false;

	dma_sync_single_for_cpu(&fep->pdev->dev,
				fec32_to_cpu(bdp->cbd_bufaddr),
				FEC_ENET_RX_FRSIZE - fep->rx_align,
				DMA_FROM_DEVICE);
	if (!swap)
		memcpy(new_skb->data, (*skb)->data, length);
	else
		swap_buffer2(new_skb->data, (*skb)->data, length);
	*skb = new_skb;

	return true;
}