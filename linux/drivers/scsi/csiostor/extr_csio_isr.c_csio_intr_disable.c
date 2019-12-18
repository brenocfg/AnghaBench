#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct csio_hw {int intr_mode; int num_sqsets; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; TYPE_1__* msix_entries; } ;
struct TYPE_2__ {struct csio_hw* dev_id; } ;

/* Variables and functions */
 int CSIO_EXTRA_VECS ; 
 int /*<<< orphan*/  CSIO_HWF_HOST_INTR_ENABLED ; 
#define  CSIO_IM_INTX 130 
#define  CSIO_IM_MSI 129 
#define  CSIO_IM_MSIX 128 
 int CSIO_IM_NONE ; 
 int /*<<< orphan*/  csio_hw_intr_disable (struct csio_hw*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct csio_hw*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

void
csio_intr_disable(struct csio_hw *hw, bool free)
{
	csio_hw_intr_disable(hw);

	if (free) {
		int i;

		switch (hw->intr_mode) {
		case CSIO_IM_MSIX:
			for (i = 0; i < hw->num_sqsets + CSIO_EXTRA_VECS; i++) {
				free_irq(pci_irq_vector(hw->pdev, i),
					 hw->msix_entries[i].dev_id);
			}
			break;
		case CSIO_IM_MSI:
		case CSIO_IM_INTX:
			free_irq(pci_irq_vector(hw->pdev, 0), hw);
			break;
		default:
			break;
		}
	}

	pci_free_irq_vectors(hw->pdev);
	hw->intr_mode = CSIO_IM_NONE;
	hw->flags &= ~CSIO_HWF_HOST_INTR_ENABLED;
}