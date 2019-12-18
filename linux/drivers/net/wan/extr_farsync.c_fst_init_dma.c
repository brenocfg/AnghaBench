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
struct fst_card_info {scalar_t__ family; scalar_t__ pci_conf; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ DMAMODE0 ; 
 scalar_t__ DMAMODE1 ; 
 scalar_t__ DMATHR ; 
 scalar_t__ FST_FAMILY_TXU ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fst_init_dma(struct fst_card_info *card)
{
	/*
	 * This is only required for the PLX 9054
	 */
	if (card->family == FST_FAMILY_TXU) {
	        pci_set_master(card->device);
		outl(0x00020441, card->pci_conf + DMAMODE0);
		outl(0x00020441, card->pci_conf + DMAMODE1);
		outl(0x0, card->pci_conf + DMATHR);
	}
}