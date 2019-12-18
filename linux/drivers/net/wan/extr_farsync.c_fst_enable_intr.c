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
struct fst_card_info {scalar_t__ family; scalar_t__ pci_conf; } ;

/* Variables and functions */
 scalar_t__ FST_FAMILY_TXU ; 
 scalar_t__ INTCSR_9052 ; 
 scalar_t__ INTCSR_9054 ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static inline void
fst_enable_intr(struct fst_card_info *card)
{
	if (card->family == FST_FAMILY_TXU) {
		outl(0x0f0c0900, card->pci_conf + INTCSR_9054);
	} else {
		outw(0x0543, card->pci_conf + INTCSR_9052);
	}
}