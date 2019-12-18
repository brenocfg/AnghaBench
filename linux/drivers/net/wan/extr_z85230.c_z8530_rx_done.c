#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct z8530_channel {int rxdma_on; int dma_ready; unsigned char** rx_buf; size_t dma_num; int mtu; int count; int max; TYPE_2__* netdevice; int /*<<< orphan*/  (* rx_function ) (struct z8530_channel*,struct sk_buff*) ;struct sk_buff* skb2; struct sk_buff* skb; int /*<<< orphan*/  dptr; int /*<<< orphan*/  rxdma; } ;
struct sk_buff {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_5__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int DMA_MODE_READ ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  RES_Rx_CRC ; 
 int /*<<< orphan*/  RT_LOCK ; 
 int /*<<< orphan*/  RT_UNLOCK ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  clear_dma_ff (int /*<<< orphan*/ ) ; 
 void* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_dma (int /*<<< orphan*/ ) ; 
 int get_dma_residue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_dma_count (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_dma_mode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct z8530_channel*,struct sk_buff*) ; 
 int /*<<< orphan*/  virt_to_bus (unsigned char*) ; 
 int /*<<< orphan*/  write_zsreg (struct z8530_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void z8530_rx_done(struct z8530_channel *c)
{
	struct sk_buff *skb;
	int ct;
	
	/*
	 *	Is our receive engine in DMA mode
	 */
	 
	if(c->rxdma_on)
	{
		/*
		 *	Save the ready state and the buffer currently
		 *	being used as the DMA target
		 */
		 
		int ready=c->dma_ready;
		unsigned char *rxb=c->rx_buf[c->dma_num];
		unsigned long flags;
		
		/*
		 *	Complete this DMA. Necessary to find the length
		 */		
		 
		flags=claim_dma_lock();
		
		disable_dma(c->rxdma);
		clear_dma_ff(c->rxdma);
		c->rxdma_on=0;
		ct=c->mtu-get_dma_residue(c->rxdma);
		if(ct<0)
			ct=2;	/* Shit happens.. */
		c->dma_ready=0;
		
		/*
		 *	Normal case: the other slot is free, start the next DMA
		 *	into it immediately.
		 */
		 
		if(ready)
		{
			c->dma_num^=1;
			set_dma_mode(c->rxdma, DMA_MODE_READ|0x10);
			set_dma_addr(c->rxdma, virt_to_bus(c->rx_buf[c->dma_num]));
			set_dma_count(c->rxdma, c->mtu);
			c->rxdma_on = 1;
			enable_dma(c->rxdma);
			/* Stop any frames that we missed the head of 
			   from passing */
			write_zsreg(c, R0, RES_Rx_CRC);
		}
		else
			/* Can't occur as we dont reenable the DMA irq until
			   after the flip is done */
			netdev_warn(c->netdevice, "DMA flip overrun!\n");

		release_dma_lock(flags);

		/*
		 *	Shove the old buffer into an sk_buff. We can't DMA
		 *	directly into one on a PC - it might be above the 16Mb
		 *	boundary. Optimisation - we could check to see if we
		 *	can avoid the copy. Optimisation 2 - make the memcpy
		 *	a copychecksum.
		 */

		skb = dev_alloc_skb(ct);
		if (skb == NULL) {
			c->netdevice->stats.rx_dropped++;
			netdev_warn(c->netdevice, "Memory squeeze\n");
		} else {
			skb_put(skb, ct);
			skb_copy_to_linear_data(skb, rxb, ct);
			c->netdevice->stats.rx_packets++;
			c->netdevice->stats.rx_bytes += ct;
		}
		c->dma_ready = 1;
	} else {
		RT_LOCK;
		skb = c->skb;

		/*
		 *	The game we play for non DMA is similar. We want to
		 *	get the controller set up for the next packet as fast
		 *	as possible. We potentially only have one byte + the
		 *	fifo length for this. Thus we want to flip to the new
		 *	buffer and then mess around copying and allocating
		 *	things. For the current case it doesn't matter but
		 *	if you build a system where the sync irq isn't blocked
		 *	by the kernel IRQ disable then you need only block the
		 *	sync IRQ for the RT_LOCK area.
		 *
		 */
		ct=c->count;

		c->skb = c->skb2;
		c->count = 0;
		c->max = c->mtu;
		if (c->skb) {
			c->dptr = c->skb->data;
			c->max = c->mtu;
		} else {
			c->count = 0;
			c->max = 0;
		}
		RT_UNLOCK;

		c->skb2 = dev_alloc_skb(c->mtu);
		if (c->skb2 == NULL)
			netdev_warn(c->netdevice, "memory squeeze\n");
		else
			skb_put(c->skb2, c->mtu);
		c->netdevice->stats.rx_packets++;
		c->netdevice->stats.rx_bytes += ct;
	}
	/*
	 *	If we received a frame we must now process it.
	 */
	if (skb) {
		skb_trim(skb, ct);
		c->rx_function(c, skb);
	} else {
		c->netdevice->stats.rx_dropped++;
		netdev_err(c->netdevice, "Lost a frame\n");
	}
}