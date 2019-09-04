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
 int /*<<< orphan*/  R_STATUS ; 
 int V_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
#ifdef HFC_REGISTER_DEBUG
HFC_wait_regio(struct hfc_multi *hc, const char *function, int line)
#else
	HFC_wait_regio(struct hfc_multi *hc)
#endif
{
	outb(R_STATUS, hc->pci_iobase + 4);
	while (inb(hc->pci_iobase) & V_BUSY)
		cpu_relax();
}