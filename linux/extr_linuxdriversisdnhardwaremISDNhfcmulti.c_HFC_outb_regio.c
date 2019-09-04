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
typedef  int /*<<< orphan*/  u_char ;
struct hfc_multi {scalar_t__ pci_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
#ifdef HFC_REGISTER_DEBUG
HFC_outb_regio(struct hfc_multi *hc, u_char reg, u_char val,
	       const char *function, int line)
#else
	HFC_outb_regio(struct hfc_multi *hc, u_char reg, u_char val)
#endif
{
	outb(reg, hc->pci_iobase + 4);
	outb(val, hc->pci_iobase);
}