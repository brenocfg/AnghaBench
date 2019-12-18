#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct page {int dummy; } ;
struct dpaa2_sg_entry {int dummy; } ;
struct dpaa2_eth_priv {int /*<<< orphan*/  iommu_domain; TYPE_2__* net_dev; } ;
struct dpaa2_eth_channel {int buf_count; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {struct device* parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DPAA2_ETH_MAX_SG_ENTRIES ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_RAW_SIZE ; 
 int /*<<< orphan*/  DPAA2_ETH_RX_BUF_SIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 struct sk_buff* build_skb (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dpaa2_iova_to_virt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_sg_get_addr (struct dpaa2_sg_entry*) ; 
 int /*<<< orphan*/  dpaa2_sg_get_len (struct dpaa2_sg_entry*) ; 
 int /*<<< orphan*/  dpaa2_sg_get_offset (struct dpaa2_sg_entry*) ; 
 scalar_t__ dpaa2_sg_is_final (struct dpaa2_sg_entry*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long page_address (struct page*) ; 
 int /*<<< orphan*/  skb_add_rx_frag (struct sk_buff*,int,struct page*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 struct page* virt_to_head_page (void*) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static struct sk_buff *build_frag_skb(struct dpaa2_eth_priv *priv,
				      struct dpaa2_eth_channel *ch,
				      struct dpaa2_sg_entry *sgt)
{
	struct sk_buff *skb = NULL;
	struct device *dev = priv->net_dev->dev.parent;
	void *sg_vaddr;
	dma_addr_t sg_addr;
	u16 sg_offset;
	u32 sg_length;
	struct page *page, *head_page;
	int page_offset;
	int i;

	for (i = 0; i < DPAA2_ETH_MAX_SG_ENTRIES; i++) {
		struct dpaa2_sg_entry *sge = &sgt[i];

		/* NOTE: We only support SG entries in dpaa2_sg_single format,
		 * but this is the only format we may receive from HW anyway
		 */

		/* Get the address and length from the S/G entry */
		sg_addr = dpaa2_sg_get_addr(sge);
		sg_vaddr = dpaa2_iova_to_virt(priv->iommu_domain, sg_addr);
		dma_unmap_page(dev, sg_addr, DPAA2_ETH_RX_BUF_SIZE,
			       DMA_BIDIRECTIONAL);

		sg_length = dpaa2_sg_get_len(sge);

		if (i == 0) {
			/* We build the skb around the first data buffer */
			skb = build_skb(sg_vaddr, DPAA2_ETH_RX_BUF_RAW_SIZE);
			if (unlikely(!skb)) {
				/* Free the first SG entry now, since we already
				 * unmapped it and obtained the virtual address
				 */
				free_pages((unsigned long)sg_vaddr, 0);

				/* We still need to subtract the buffers used
				 * by this FD from our software counter
				 */
				while (!dpaa2_sg_is_final(&sgt[i]) &&
				       i < DPAA2_ETH_MAX_SG_ENTRIES)
					i++;
				break;
			}

			sg_offset = dpaa2_sg_get_offset(sge);
			skb_reserve(skb, sg_offset);
			skb_put(skb, sg_length);
		} else {
			/* Rest of the data buffers are stored as skb frags */
			page = virt_to_page(sg_vaddr);
			head_page = virt_to_head_page(sg_vaddr);

			/* Offset in page (which may be compound).
			 * Data in subsequent SG entries is stored from the
			 * beginning of the buffer, so we don't need to add the
			 * sg_offset.
			 */
			page_offset = ((unsigned long)sg_vaddr &
				(PAGE_SIZE - 1)) +
				(page_address(page) - page_address(head_page));

			skb_add_rx_frag(skb, i - 1, head_page, page_offset,
					sg_length, DPAA2_ETH_RX_BUF_SIZE);
		}

		if (dpaa2_sg_is_final(sge))
			break;
	}

	WARN_ONCE(i == DPAA2_ETH_MAX_SG_ENTRIES, "Final bit not set in SGT");

	/* Count all data buffers + SG table buffer */
	ch->buf_count -= i + 2;

	return skb;
}