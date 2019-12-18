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
typedef  int u16 ;
struct peak_canfd_priv {int dummy; } ;
struct pciefd_tx_link {void* laddr_hi; void* laddr_lo; void* type; void* size; } ;
struct pciefd_page {int offset; int size; int lbase; struct pciefd_tx_link* vbase; } ;
struct pciefd_can {int tx_page_index; int tx_pages_free; int /*<<< orphan*/  tx_lock; struct pciefd_page* tx_pages; } ;

/* Variables and functions */
 int CANFD_MSG_LNK_TX ; 
 int PCIEFD_TX_PAGE_COUNT ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void *pciefd_alloc_tx_msg(struct peak_canfd_priv *ucan, u16 msg_size,
				 int *room_left)
{
	struct pciefd_can *priv = (struct pciefd_can *)ucan;
	struct pciefd_page *page = priv->tx_pages + priv->tx_page_index;
	unsigned long flags;
	void *msg;

	spin_lock_irqsave(&priv->tx_lock, flags);

	if (page->offset + msg_size > page->size) {
		struct pciefd_tx_link *lk;

		/* not enough space in this page: try another one */
		if (!priv->tx_pages_free) {
			spin_unlock_irqrestore(&priv->tx_lock, flags);

			/* Tx overflow */
			return NULL;
		}

		priv->tx_pages_free--;

		/* keep address of the very last free slot of current page */
		lk = page->vbase + page->offset;

		/* next, move on a new free page */
		priv->tx_page_index = (priv->tx_page_index + 1) %
				      PCIEFD_TX_PAGE_COUNT;
		page = priv->tx_pages + priv->tx_page_index;

		/* put link record to this new page at the end of prev one */
		lk->size = cpu_to_le16(sizeof(*lk));
		lk->type = cpu_to_le16(CANFD_MSG_LNK_TX);
		lk->laddr_lo = cpu_to_le32(page->lbase);

#ifdef CONFIG_ARCH_DMA_ADDR_T_64BIT
		lk->laddr_hi = cpu_to_le32(page->lbase >> 32);
#else
		lk->laddr_hi = 0;
#endif
		/* next msgs will be put from the begininng of this new page */
		page->offset = 0;
	}

	*room_left = priv->tx_pages_free * page->size;

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	msg = page->vbase + page->offset;

	/* give back room left in the tx ring */
	*room_left += page->size - (page->offset + msg_size);

	return msg;
}