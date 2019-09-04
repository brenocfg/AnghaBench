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
struct msix_entry {int /*<<< orphan*/  vector; } ;
struct adf_hw_device_data {int num_banks; } ;
struct adf_etr_data {struct adf_accel_dev* banks; } ;
struct TYPE_2__ {int num_entries; struct msix_entry* entries; } ;
struct adf_accel_pci {TYPE_1__ msix_entries; } ;
struct adf_accel_dev {struct adf_etr_data* transport; struct adf_hw_device_data* hw_device; struct adf_accel_pci accel_pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct adf_accel_dev*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void adf_free_irqs(struct adf_accel_dev *accel_dev)
{
	struct adf_accel_pci *pci_dev_info = &accel_dev->accel_pci_dev;
	struct adf_hw_device_data *hw_data = accel_dev->hw_device;
	struct msix_entry *msixe = pci_dev_info->msix_entries.entries;
	struct adf_etr_data *etr_data = accel_dev->transport;
	int i = 0;

	if (pci_dev_info->msix_entries.num_entries > 1) {
		for (i = 0; i < hw_data->num_banks; i++) {
			irq_set_affinity_hint(msixe[i].vector, NULL);
			free_irq(msixe[i].vector, &etr_data->banks[i]);
		}
	}
	irq_set_affinity_hint(msixe[i].vector, NULL);
	free_irq(msixe[i].vector, accel_dev);
}