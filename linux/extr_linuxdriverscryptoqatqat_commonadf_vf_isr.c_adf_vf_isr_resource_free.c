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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct adf_accel_dev {int dummy; } ;

/* Variables and functions */
 struct pci_dev* accel_to_pci_dev (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_cleanup_bh (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_cleanup_pf2vf_bh (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  adf_disable_msi (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void adf_vf_isr_resource_free(struct adf_accel_dev *accel_dev)
{
	struct pci_dev *pdev = accel_to_pci_dev(accel_dev);

	irq_set_affinity_hint(pdev->irq, NULL);
	free_irq(pdev->irq, (void *)accel_dev);
	adf_cleanup_bh(accel_dev);
	adf_cleanup_pf2vf_bh(accel_dev);
	adf_disable_msi(accel_dev);
}