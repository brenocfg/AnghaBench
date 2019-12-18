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
struct adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  pf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROMPFSIZE ; 
 int pci_read_vpd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int t4_eeprom_ptov (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cudbg_read_vpd_reg(struct adapter *padap, u32 addr, u32 len,
			      void *dest)
{
	int vaddr, rc;

	vaddr = t4_eeprom_ptov(addr, padap->pf, EEPROMPFSIZE);
	if (vaddr < 0)
		return vaddr;

	rc = pci_read_vpd(padap->pdev, vaddr, len, dest);
	if (rc < 0)
		return rc;

	return 0;
}