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
 unsigned int PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 int PCI_HEADER_TYPE ; 
 int PCI_STATUS ; 

__attribute__((used)) static bool type1_access_ok(unsigned int bus, unsigned int devfn, int reg)
{
	/*
	 * This is a workaround for A0 LNC bug where PCI status register does
	 * not have new CAP bit set. can not be written by SW either.
	 *
	 * PCI header type in real LNC indicates a single function device, this
	 * will prevent probing other devices under the same function in PCI
	 * shim. Therefore, use the header type in shim instead.
	 */
	if (reg >= 0x100 || reg == PCI_STATUS || reg == PCI_HEADER_TYPE)
		return false;
	if (bus == 0 && (devfn == PCI_DEVFN(2, 0)
				|| devfn == PCI_DEVFN(0, 0)
				|| devfn == PCI_DEVFN(3, 0)))
		return true;
	return false; /* Langwell on others */
}