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
struct pci_dev {int dummy; } ;
struct bt878 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct bt878* bt878 ; 
 unsigned int bt878_num ; 
 scalar_t__ is_pci_slot_eq (int /*<<< orphan*/ ,struct pci_dev*) ; 

__attribute__((used)) static struct bt878 *dvb_bt8xx_878_match(unsigned int bttv_nr,
					 struct pci_dev* bttv_pci_dev)
{
	unsigned int card_nr;

	/* Hmm, n squared. Hope n is small */
	for (card_nr = 0; card_nr < bt878_num; card_nr++)
		if (is_pci_slot_eq(bt878[card_nr].dev, bttv_pci_dev))
			return &bt878[card_nr];
	return NULL;
}