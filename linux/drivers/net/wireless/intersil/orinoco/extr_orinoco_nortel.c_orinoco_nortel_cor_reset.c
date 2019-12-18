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
struct orinoco_private {struct orinoco_pci_card* card; } ;
struct orinoco_pci_card {scalar_t__ bridge_io; scalar_t__ attr_io; } ;

/* Variables and functions */
 scalar_t__ COR_OFFSET ; 
 int COR_VALUE ; 
 int /*<<< orphan*/  ioread16 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int orinoco_nortel_cor_reset(struct orinoco_private *priv)
{
	struct orinoco_pci_card *card = priv->card;

	/* Assert the reset until the card notices */
	iowrite16(8, card->bridge_io + 2);
	ioread16(card->attr_io + COR_OFFSET);
	iowrite16(0x80, card->attr_io + COR_OFFSET);
	mdelay(1);

	/* Give time for the card to recover from this hard effort */
	iowrite16(0, card->attr_io + COR_OFFSET);
	iowrite16(0, card->attr_io + COR_OFFSET);
	mdelay(1);

	/* Set COR as usual */
	iowrite16(COR_VALUE, card->attr_io + COR_OFFSET);
	iowrite16(COR_VALUE, card->attr_io + COR_OFFSET);
	mdelay(1);

	iowrite16(0x228, card->bridge_io + 2);

	return 0;
}