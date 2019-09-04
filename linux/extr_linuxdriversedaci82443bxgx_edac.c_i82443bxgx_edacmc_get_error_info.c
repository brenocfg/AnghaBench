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
struct pci_dev {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; } ;
struct i82443bxgx_edacmc_error_info {int eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I82443BXGX_EAP ; 
 int I82443BXGX_EAP_OFFSET_MBE ; 
 int I82443BXGX_EAP_OFFSET_SBE ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_bits32 (struct pci_dev*,int /*<<< orphan*/ ,int,int) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i82443bxgx_edacmc_get_error_info(struct mem_ctl_info *mci,
				struct i82443bxgx_edacmc_error_info
				*info)
{
	struct pci_dev *pdev;
	pdev = to_pci_dev(mci->pdev);
	pci_read_config_dword(pdev, I82443BXGX_EAP, &info->eap);
	if (info->eap & I82443BXGX_EAP_OFFSET_SBE)
		/* Clear error to allow next error to be reported [p.61] */
		pci_write_bits32(pdev, I82443BXGX_EAP,
				 I82443BXGX_EAP_OFFSET_SBE,
				 I82443BXGX_EAP_OFFSET_SBE);

	if (info->eap & I82443BXGX_EAP_OFFSET_MBE)
		/* Clear error to allow next error to be reported [p.61] */
		pci_write_bits32(pdev, I82443BXGX_EAP,
				 I82443BXGX_EAP_OFFSET_MBE,
				 I82443BXGX_EAP_OFFSET_MBE);
}