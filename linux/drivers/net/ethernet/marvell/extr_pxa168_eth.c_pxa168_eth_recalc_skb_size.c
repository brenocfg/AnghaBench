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
struct pxa168_eth_private {int skb_size; TYPE_1__* dev; } ;
struct TYPE_2__ {int mtu; } ;

/* Variables and functions */
 scalar_t__ SKB_DMA_REALIGN ; 

__attribute__((used)) static void pxa168_eth_recalc_skb_size(struct pxa168_eth_private *pep)
{
	int skb_size;

	/*
	 * Reserve 2+14 bytes for an ethernet header (the hardware
	 * automatically prepends 2 bytes of dummy data to each
	 * received packet), 16 bytes for up to four VLAN tags, and
	 * 4 bytes for the trailing FCS -- 36 bytes total.
	 */
	skb_size = pep->dev->mtu + 36;

	/*
	 * Make sure that the skb size is a multiple of 8 bytes, as
	 * the lower three bits of the receive descriptor's buffer
	 * size field are ignored by the hardware.
	 */
	pep->skb_size = (skb_size + 7) & ~7;

	/*
	 * If NET_SKB_PAD is smaller than a cache line,
	 * netdev_alloc_skb() will cause skb->data to be misaligned
	 * to a cache line boundary.  If this is the case, include
	 * some extra space to allow re-aligning the data area.
	 */
	pep->skb_size += SKB_DMA_REALIGN;

}