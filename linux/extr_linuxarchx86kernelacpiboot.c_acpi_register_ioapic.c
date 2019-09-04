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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int ENOSYS ; 

int acpi_register_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base)
{
	int ret = -ENOSYS;
#ifdef CONFIG_ACPI_HOTPLUG_IOAPIC
	int ioapic_id;
	u64 addr;
	struct ioapic_domain_cfg cfg = {
		.type = IOAPIC_DOMAIN_DYNAMIC,
		.ops = &mp_ioapic_irqdomain_ops,
	};

	ioapic_id = acpi_get_ioapic_id(handle, gsi_base, &addr);
	if (ioapic_id < 0) {
		unsigned long long uid;
		acpi_status status;

		status = acpi_evaluate_integer(handle, METHOD_NAME__UID,
					       NULL, &uid);
		if (ACPI_FAILURE(status)) {
			acpi_handle_warn(handle, "failed to get IOAPIC ID.\n");
			return -EINVAL;
		}
		ioapic_id = (int)uid;
	}

	mutex_lock(&acpi_ioapic_lock);
	ret  = mp_register_ioapic(ioapic_id, phys_addr, gsi_base, &cfg);
	mutex_unlock(&acpi_ioapic_lock);
#endif

	return ret;
}