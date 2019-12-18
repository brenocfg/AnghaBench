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
 int pci_write_vpd (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int t4_eeprom_ptov (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eeprom_wr_phys(struct adapter *adap, unsigned int phys_addr, u32 v)
{
	int vaddr = t4_eeprom_ptov(phys_addr, adap->pf, EEPROMPFSIZE);

	if (vaddr >= 0)
		vaddr = pci_write_vpd(adap->pdev, vaddr, sizeof(u32), &v);
	return vaddr < 0 ? vaddr : 0;
}