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
 int /*<<< orphan*/  NFORCE2_PLLADR ; 
 int /*<<< orphan*/  NFORCE2_PLLREG ; 
 int /*<<< orphan*/  nforce2_dev ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nforce2_write_pll(int pll)
{
	int temp;

	/* Set the pll addr. to 0x00 */
	pci_write_config_dword(nforce2_dev, NFORCE2_PLLADR, 0);

	/* Now write the value in all 64 registers */
	for (temp = 0; temp <= 0x3f; temp++)
		pci_write_config_dword(nforce2_dev, NFORCE2_PLLREG, pll);

	return;
}