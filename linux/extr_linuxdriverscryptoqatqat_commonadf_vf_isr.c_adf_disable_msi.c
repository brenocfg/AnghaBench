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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_name; } ;
struct adf_accel_dev {TYPE_1__ vf; } ;

/* Variables and functions */
 struct pci_dev* accel_to_pci_dev (struct adf_accel_dev*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 

__attribute__((used)) static void adf_disable_msi(struct adf_accel_dev *accel_dev)
{
	struct pci_dev *pdev = accel_to_pci_dev(accel_dev);

	kfree(accel_dev->vf.irq_name);
	pci_disable_msi(pdev);
}