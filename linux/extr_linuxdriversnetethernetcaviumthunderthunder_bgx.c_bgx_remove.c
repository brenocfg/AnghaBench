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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct bgx {scalar_t__ lmac_count; size_t bgx_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgx_lmac_disable (struct bgx*,scalar_t__) ; 
 int /*<<< orphan*/ ** bgx_vnic ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct bgx* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bgx_remove(struct pci_dev *pdev)
{
	struct bgx *bgx = pci_get_drvdata(pdev);
	u8 lmac;

	/* Disable all LMACs */
	for (lmac = 0; lmac < bgx->lmac_count; lmac++)
		bgx_lmac_disable(bgx, lmac);

	bgx_vnic[bgx->bgx_id] = NULL;
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);
}