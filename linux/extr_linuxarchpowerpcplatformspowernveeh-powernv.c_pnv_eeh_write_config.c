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
typedef  int /*<<< orphan*/  u32 ;
struct pci_dn {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SET_FAILED ; 
 scalar_t__ pnv_eeh_cfg_blocked (struct pci_dn*) ; 
 int pnv_pci_cfg_write (struct pci_dn*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pnv_eeh_write_config(struct pci_dn *pdn,
				int where, int size, u32 val)
{
	if (!pdn)
		return PCIBIOS_DEVICE_NOT_FOUND;

	if (pnv_eeh_cfg_blocked(pdn))
		return PCIBIOS_SET_FAILED;

	return pnv_pci_cfg_write(pdn, where, size, val);
}