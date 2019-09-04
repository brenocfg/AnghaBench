#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {scalar_t__ data; } ;
struct TYPE_7__ {scalar_t__ base; } ;
struct TYPE_6__ {scalar_t__ base; } ;
struct idt77252_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; scalar_t__ membase; scalar_t__* fbq; TYPE_4__* pcidev; TYPE_3__ tsq; TYPE_2__ rsq; int /*<<< orphan*/  raw_cell_paddr; scalar_t__ raw_cell_hnd; int /*<<< orphan*/  vcs; int /*<<< orphan*/  scd2vc; int /*<<< orphan*/  soft_tst; TYPE_1__* sbpool; scalar_t__ atmdev; int /*<<< orphan*/  index; } ;
struct TYPE_8__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {struct sk_buff** skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIPRINTK (char*,...) ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int FBQ_SIZE ; 
 int /*<<< orphan*/  IDT77252_BIT_INIT ; 
 int /*<<< orphan*/  IDT77252_PRV_PADDR (struct sk_buff*) ; 
 int /*<<< orphan*/  SAR_REG_CFG ; 
 int /*<<< orphan*/  atm_dev_deregister (scalar_t__) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deinit_rsq (struct idt77252_dev*) ; 
 int /*<<< orphan*/  deinit_tsq (struct idt77252_dev*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct idt77252_dev*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_end_pointer (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
deinit_card(struct idt77252_dev *card)
{
	struct sk_buff *skb;
	int i, j;

	if (!test_bit(IDT77252_BIT_INIT, &card->flags)) {
		printk("%s: SAR not yet initialized.\n", card->name);
		return;
	}
	DIPRINTK("idt77252: deinitialize card %u\n", card->index);

	writel(0, SAR_REG_CFG);

	if (card->atmdev)
		atm_dev_deregister(card->atmdev);

	for (i = 0; i < 4; i++) {
		for (j = 0; j < FBQ_SIZE; j++) {
			skb = card->sbpool[i].skb[j];
			if (skb) {
				dma_unmap_single(&card->pcidev->dev,
						 IDT77252_PRV_PADDR(skb),
						 (skb_end_pointer(skb) -
						  skb->data),
						 DMA_FROM_DEVICE);
				card->sbpool[i].skb[j] = NULL;
				dev_kfree_skb(skb);
			}
		}
	}

	vfree(card->soft_tst);

	vfree(card->scd2vc);

	vfree(card->vcs);

	if (card->raw_cell_hnd) {
		dma_free_coherent(&card->pcidev->dev, 2 * sizeof(u32),
				  card->raw_cell_hnd, card->raw_cell_paddr);
	}

	if (card->rsq.base) {
		DIPRINTK("%s: Release RSQ ...\n", card->name);
		deinit_rsq(card);
	}

	if (card->tsq.base) {
		DIPRINTK("%s: Release TSQ ...\n", card->name);
		deinit_tsq(card);
	}

	DIPRINTK("idt77252: Release IRQ.\n");
	free_irq(card->pcidev->irq, card);

	for (i = 0; i < 4; i++) {
		if (card->fbq[i])
			iounmap(card->fbq[i]);
	}

	if (card->membase)
		iounmap(card->membase);

	clear_bit(IDT77252_BIT_INIT, &card->flags);
	DIPRINTK("%s: Card deinitialized.\n", card->name);
}