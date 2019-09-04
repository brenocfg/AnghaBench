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
struct sk_buff {int /*<<< orphan*/  data; } ;
struct sbmacdma {int /*<<< orphan*/  sbdma_dscrcnt; struct sbdmadscr* sbdma_addptr; struct sbdmadscr* sbdma_dscrtable; struct sk_buff** sbdma_ctxtable; struct sbdmadscr* sbdma_remptr; } ;
struct sbmac_softc {struct net_device* sbm_dev; } ;
struct sbdmadscr {int dscr_a; scalar_t__ dscr_b; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENET_PACKET_SIZE ; 
 int ENOBUFS ; 
 int ENOSPC ; 
 int M_DMA_DSCRA_INTERRUPT ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  NUMCACHEBLKS (scalar_t__) ; 
 struct sbdmadscr* SBDMA_NEXTBUF (struct sbmacdma*,int /*<<< orphan*/ ) ; 
 int SMP_CACHE_BYTES ; 
 int V_DMA_DSCRA_A_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeq (int,int /*<<< orphan*/ ) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  sbdma_addptr ; 
 int /*<<< orphan*/  sbdma_align_skb (struct sk_buff*,int,scalar_t__) ; 
 int virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbdma_add_rcvbuffer(struct sbmac_softc *sc, struct sbmacdma *d,
			       struct sk_buff *sb)
{
	struct net_device *dev = sc->sbm_dev;
	struct sbdmadscr *dsc;
	struct sbdmadscr *nextdsc;
	struct sk_buff *sb_new = NULL;
	int pktsize = ENET_PACKET_SIZE;

	/* get pointer to our current place in the ring */

	dsc = d->sbdma_addptr;
	nextdsc = SBDMA_NEXTBUF(d,sbdma_addptr);

	/*
	 * figure out if the ring is full - if the next descriptor
	 * is the same as the one that we're going to remove from
	 * the ring, the ring is full
	 */

	if (nextdsc == d->sbdma_remptr) {
		return -ENOSPC;
	}

	/*
	 * Allocate a sk_buff if we don't already have one.
	 * If we do have an sk_buff, reset it so that it's empty.
	 *
	 * Note: sk_buffs don't seem to be guaranteed to have any sort
	 * of alignment when they are allocated.  Therefore, allocate enough
	 * extra space to make sure that:
	 *
	 *    1. the data does not start in the middle of a cache line.
	 *    2. The data does not end in the middle of a cache line
	 *    3. The buffer can be aligned such that the IP addresses are
	 *       naturally aligned.
	 *
	 *  Remember, the SOCs MAC writes whole cache lines at a time,
	 *  without reading the old contents first.  So, if the sk_buff's
	 *  data portion starts in the middle of a cache line, the SOC
	 *  DMA will trash the beginning (and ending) portions.
	 */

	if (sb == NULL) {
		sb_new = netdev_alloc_skb(dev, ENET_PACKET_SIZE +
					       SMP_CACHE_BYTES * 2 +
					       NET_IP_ALIGN);
		if (sb_new == NULL)
			return -ENOBUFS;

		sbdma_align_skb(sb_new, SMP_CACHE_BYTES, NET_IP_ALIGN);
	}
	else {
		sb_new = sb;
		/*
		 * nothing special to reinit buffer, it's already aligned
		 * and sb->data already points to a good place.
		 */
	}

	/*
	 * fill in the descriptor
	 */

#ifdef CONFIG_SBMAC_COALESCE
	/*
	 * Do not interrupt per DMA transfer.
	 */
	dsc->dscr_a = virt_to_phys(sb_new->data) |
		V_DMA_DSCRA_A_SIZE(NUMCACHEBLKS(pktsize + NET_IP_ALIGN)) | 0;
#else
	dsc->dscr_a = virt_to_phys(sb_new->data) |
		V_DMA_DSCRA_A_SIZE(NUMCACHEBLKS(pktsize + NET_IP_ALIGN)) |
		M_DMA_DSCRA_INTERRUPT;
#endif

	/* receiving: no options */
	dsc->dscr_b = 0;

	/*
	 * fill in the context
	 */

	d->sbdma_ctxtable[dsc-d->sbdma_dscrtable] = sb_new;

	/*
	 * point at next packet
	 */

	d->sbdma_addptr = nextdsc;

	/*
	 * Give the buffer to the DMA engine.
	 */

	__raw_writeq(1, d->sbdma_dscrcnt);

	return 0;					/* we did it */
}