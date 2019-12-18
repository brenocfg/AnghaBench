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
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  brcmf_pciedrvr ; 
 int pci_register_driver (int /*<<< orphan*/ *) ; 

void brcmf_pcie_register(void)
{
	int err;

	brcmf_dbg(PCIE, "Enter\n");
	err = pci_register_driver(&brcmf_pciedrvr);
	if (err)
		brcmf_err(NULL, "PCIE driver registration failed, err=%d\n",
			  err);
}