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
struct pqi_ctrl_info {scalar_t__ num_msix_vectors_enabled; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_disable_msix_interrupts(struct pqi_ctrl_info *ctrl_info)
{
	if (ctrl_info->num_msix_vectors_enabled) {
		pci_free_irq_vectors(ctrl_info->pci_dev);
		ctrl_info->num_msix_vectors_enabled = 0;
	}
}