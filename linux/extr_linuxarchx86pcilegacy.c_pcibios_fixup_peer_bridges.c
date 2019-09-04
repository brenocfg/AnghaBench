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

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int pcibios_last_bus ; 
 int /*<<< orphan*/  pcibios_scan_specific_bus (int) ; 

__attribute__((used)) static void pcibios_fixup_peer_bridges(void)
{
	int n;

	if (pcibios_last_bus <= 0 || pcibios_last_bus > 0xff)
		return;
	DBG("PCI: Peer bridge fixup\n");

	for (n=0; n <= pcibios_last_bus; n++)
		pcibios_scan_specific_bus(n);
}