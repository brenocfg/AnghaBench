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
struct gelic_descr_chain {struct gelic_descr* tail; struct gelic_descr* head; } ;
struct gelic_descr {scalar_t__ bus_addr; scalar_t__ next_descr_addr; struct gelic_descr* next; struct gelic_descr* prev; } ;
struct gelic_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GELIC_DESCR_DMA_NOT_IN_USE ; 
 int /*<<< orphan*/  GELIC_DESCR_SIZE ; 
 scalar_t__ cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  ctodev (struct gelic_card*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ ,struct gelic_descr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gelic_descr_set_status (struct gelic_descr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gelic_descr*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gelic_card_init_chain(struct gelic_card *card,
				 struct gelic_descr_chain *chain,
				 struct gelic_descr *start_descr, int no)
{
	int i;
	struct gelic_descr *descr;

	descr = start_descr;
	memset(descr, 0, sizeof(*descr) * no);

	/* set up the hardware pointers in each descriptor */
	for (i = 0; i < no; i++, descr++) {
		gelic_descr_set_status(descr, GELIC_DESCR_DMA_NOT_IN_USE);
		descr->bus_addr =
			dma_map_single(ctodev(card), descr,
				       GELIC_DESCR_SIZE,
				       DMA_BIDIRECTIONAL);

		if (!descr->bus_addr)
			goto iommu_error;

		descr->next = descr + 1;
		descr->prev = descr - 1;
	}
	/* make them as ring */
	(descr - 1)->next = start_descr;
	start_descr->prev = (descr - 1);

	/* chain bus addr of hw descriptor */
	descr = start_descr;
	for (i = 0; i < no; i++, descr++) {
		descr->next_descr_addr = cpu_to_be32(descr->next->bus_addr);
	}

	chain->head = start_descr;
	chain->tail = start_descr;

	/* do not chain last hw descriptor */
	(descr - 1)->next_descr_addr = 0;

	return 0;

iommu_error:
	for (i--, descr--; 0 <= i; i--, descr--)
		if (descr->bus_addr)
			dma_unmap_single(ctodev(card), descr->bus_addr,
					 GELIC_DESCR_SIZE,
					 DMA_BIDIRECTIONAL);
	return -ENOMEM;
}