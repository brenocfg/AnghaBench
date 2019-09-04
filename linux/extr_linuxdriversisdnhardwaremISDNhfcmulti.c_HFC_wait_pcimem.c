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
struct hfc_multi {scalar_t__ pci_membase; } ;

/* Variables and functions */
 scalar_t__ R_STATUS ; 
 int V_BUSY ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readb (scalar_t__) ; 

__attribute__((used)) static void
#ifdef HFC_REGISTER_DEBUG
HFC_wait_pcimem(struct hfc_multi *hc, const char *function, int line)
#else
	HFC_wait_pcimem(struct hfc_multi *hc)
#endif
{
	while (readb(hc->pci_membase + R_STATUS) & V_BUSY)
		cpu_relax();
}