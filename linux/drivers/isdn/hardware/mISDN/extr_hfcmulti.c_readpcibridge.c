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
struct hfc_multi {scalar_t__ pci_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFC_outb (struct hfc_multi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  R_CTRL ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 

__attribute__((used)) static inline unsigned char
readpcibridge(struct hfc_multi *hc, unsigned char address)
{
	unsigned short cipv;
	unsigned char data;

	if (!hc->pci_iobase)
		return 0;

	/* slow down a PCI read access by 1 PCI clock cycle */
	HFC_outb(hc, R_CTRL, 0x4); /*was _io before*/

	if (address == 0)
		cipv = 0x4000;
	else
		cipv = 0x5800;

	/* select local bridge port address by writing to CIP port */
	/* data = HFC_inb(c, cipv); * was _io before */
	outw(cipv, hc->pci_iobase + 4);
	data = inb(hc->pci_iobase);

	/* restore R_CTRL for normal PCI read cycle speed */
	HFC_outb(hc, R_CTRL, 0x0); /* was _io before */

	return data;
}