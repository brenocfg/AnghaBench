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
struct pnv_phb {int /*<<< orphan*/  opal_id; } ;
struct pci_controller {struct pnv_phb* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_ASSERT_RESET ; 
 int /*<<< orphan*/  OPAL_RESET_PCI_IODA_TABLE ; 
 int /*<<< orphan*/  opal_pci_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_pci_ioda_shutdown(struct pci_controller *hose)
{
	struct pnv_phb *phb = hose->private_data;

	opal_pci_reset(phb->opal_id, OPAL_RESET_PCI_IODA_TABLE,
		       OPAL_ASSERT_RESET);
}