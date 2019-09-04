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
struct vc_map {struct atm_vcc* tx_vcc; } ;
struct idt77252_dev {int tct_size; scalar_t__ tct_base; struct vc_map** vcs; int /*<<< orphan*/ * irqstat; } ;
struct atm_vcc {int vpi; int vci; } ;
struct atm_dev {struct idt77252_dev* dev_data; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int SAR_SRAM_TCT_SIZE ; 
 int read_sram (struct idt77252_dev*,unsigned long) ; 
 int sprintf (char*,char*,...) ; 

__attribute__((used)) static int
idt77252_proc_read(struct atm_dev *dev, loff_t * pos, char *page)
{
	struct idt77252_dev *card = dev->dev_data;
	int i, left;

	left = (int) *pos;
	if (!left--)
		return sprintf(page, "IDT77252 Interrupts:\n");
	if (!left--)
		return sprintf(page, "TSIF:  %lu\n", card->irqstat[15]);
	if (!left--)
		return sprintf(page, "TXICP: %lu\n", card->irqstat[14]);
	if (!left--)
		return sprintf(page, "TSQF:  %lu\n", card->irqstat[12]);
	if (!left--)
		return sprintf(page, "TMROF: %lu\n", card->irqstat[11]);
	if (!left--)
		return sprintf(page, "PHYI:  %lu\n", card->irqstat[10]);
	if (!left--)
		return sprintf(page, "FBQ3A: %lu\n", card->irqstat[8]);
	if (!left--)
		return sprintf(page, "FBQ2A: %lu\n", card->irqstat[7]);
	if (!left--)
		return sprintf(page, "RSQF:  %lu\n", card->irqstat[6]);
	if (!left--)
		return sprintf(page, "EPDU:  %lu\n", card->irqstat[5]);
	if (!left--)
		return sprintf(page, "RAWCF: %lu\n", card->irqstat[4]);
	if (!left--)
		return sprintf(page, "FBQ1A: %lu\n", card->irqstat[3]);
	if (!left--)
		return sprintf(page, "FBQ0A: %lu\n", card->irqstat[2]);
	if (!left--)
		return sprintf(page, "RSQAF: %lu\n", card->irqstat[1]);
	if (!left--)
		return sprintf(page, "IDT77252 Transmit Connection Table:\n");

	for (i = 0; i < card->tct_size; i++) {
		unsigned long tct;
		struct atm_vcc *vcc;
		struct vc_map *vc;
		char *p;

		vc = card->vcs[i];
		if (!vc)
			continue;

		vcc = NULL;
		if (vc->tx_vcc)
			vcc = vc->tx_vcc;
		if (!vcc)
			continue;
		if (left--)
			continue;

		p = page;
		p += sprintf(p, "  %4u: %u.%u: ", i, vcc->vpi, vcc->vci);
		tct = (unsigned long) (card->tct_base + i * SAR_SRAM_TCT_SIZE);

		for (i = 0; i < 8; i++)
			p += sprintf(p, " %08x", read_sram(card, tct + i));
		p += sprintf(p, "\n");
		return p - page;
	}
	return 0;
}