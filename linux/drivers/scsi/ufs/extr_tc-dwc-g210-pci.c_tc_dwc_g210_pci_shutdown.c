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
struct ufs_hba {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  ufshcd_shutdown (struct ufs_hba*) ; 

__attribute__((used)) static void tc_dwc_g210_pci_shutdown(struct pci_dev *pdev)
{
	ufshcd_shutdown((struct ufs_hba *)pci_get_drvdata(pdev));
}