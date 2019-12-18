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
struct brcmf_pciedev_info {int dummy; } ;

/* Variables and functions */
 int BRCMF_PCIE_MB_INT_D2H_DB ; 
 int BRCMF_PCIE_MB_INT_FN0_0 ; 
 int BRCMF_PCIE_MB_INT_FN0_1 ; 
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_MAILBOXMASK ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcmf_pcie_intr_enable(struct brcmf_pciedev_info *devinfo)
{
	brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXMASK,
			       BRCMF_PCIE_MB_INT_D2H_DB |
			       BRCMF_PCIE_MB_INT_FN0_0 |
			       BRCMF_PCIE_MB_INT_FN0_1);
}