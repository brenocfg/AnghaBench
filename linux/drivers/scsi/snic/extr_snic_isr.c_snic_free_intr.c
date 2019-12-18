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
struct snic {TYPE_1__* msix; int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  devid; scalar_t__ requested; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

void
snic_free_intr(struct snic *snic)
{
	int i;

	/* ONLY interrupt mode MSIX is supported */
	for (i = 0; i < ARRAY_SIZE(snic->msix); i++) {
		if (snic->msix[i].requested) {
			free_irq(pci_irq_vector(snic->pdev, i),
				 snic->msix[i].devid);
		}
	}
}