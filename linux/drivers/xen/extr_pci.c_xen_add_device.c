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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct physdev_pci_device_add {unsigned long long* optarr; int is_virtfn; int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; TYPE_1__ physfn; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct physdev_manage_pci_ext {unsigned long long* optarr; int is_virtfn; int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; TYPE_1__ physfn; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct physdev_manage_pci {unsigned long long* optarr; int is_virtfn; int is_extfn; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; TYPE_1__ physfn; int /*<<< orphan*/  flags; scalar_t__ seg; } ;
struct pci_dev {int /*<<< orphan*/  devfn; struct pci_bus* bus; scalar_t__ is_virtfn; int /*<<< orphan*/  dev; struct pci_dev* physfn; } ;
struct pci_bus {int /*<<< orphan*/  number; struct pci_bus* parent; int /*<<< orphan*/ * bridge; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENOSYS ; 
 int HYPERVISOR_physdev_op (int /*<<< orphan*/ ,struct physdev_pci_device_add*) ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHYSDEVOP_manage_pci_add ; 
 int /*<<< orphan*/  PHYSDEVOP_manage_pci_add_ext ; 
 int /*<<< orphan*/  PHYSDEVOP_pci_device_add ; 
 int /*<<< orphan*/  XEN_PCI_DEV_EXTFN ; 
 int /*<<< orphan*/  XEN_PCI_DEV_PXM ; 
 int /*<<< orphan*/  XEN_PCI_DEV_VIRTFN ; 
 int /*<<< orphan*/  acpi_evaluate_integer (scalar_t__,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_get_parent (scalar_t__,scalar_t__*) ; 
 scalar_t__ acpi_pci_get_bridge_handle (struct pci_bus*) ; 
 scalar_t__ pci_ari_enabled (struct pci_bus*) ; 
 scalar_t__ pci_domain_nr (struct pci_bus*) ; 
 int pci_seg_supported ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  xen_mcfg_late () ; 

__attribute__((used)) static int xen_add_device(struct device *dev)
{
	int r;
	struct pci_dev *pci_dev = to_pci_dev(dev);
#ifdef CONFIG_PCI_IOV
	struct pci_dev *physfn = pci_dev->physfn;
#endif
#ifdef CONFIG_PCI_MMCONFIG
	static bool pci_mcfg_reserved = false;
	/*
	 * Reserve MCFG areas in Xen on first invocation due to this being
	 * potentially called from inside of acpi_init immediately after
	 * MCFG table has been finally parsed.
	 */
	if (!pci_mcfg_reserved) {
		xen_mcfg_late();
		pci_mcfg_reserved = true;
	}
#endif
	if (pci_seg_supported) {
		struct {
			struct physdev_pci_device_add add;
			uint32_t pxm;
		} add_ext = {
			.add.seg = pci_domain_nr(pci_dev->bus),
			.add.bus = pci_dev->bus->number,
			.add.devfn = pci_dev->devfn
		};
		struct physdev_pci_device_add *add = &add_ext.add;

#ifdef CONFIG_ACPI
		acpi_handle handle;
#endif

#ifdef CONFIG_PCI_IOV
		if (pci_dev->is_virtfn) {
			add->flags = XEN_PCI_DEV_VIRTFN;
			add->physfn.bus = physfn->bus->number;
			add->physfn.devfn = physfn->devfn;
		} else
#endif
		if (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn))
			add->flags = XEN_PCI_DEV_EXTFN;

#ifdef CONFIG_ACPI
		handle = ACPI_HANDLE(&pci_dev->dev);
#ifdef CONFIG_PCI_IOV
		if (!handle && pci_dev->is_virtfn)
			handle = ACPI_HANDLE(physfn->bus->bridge);
#endif
		if (!handle) {
			/*
			 * This device was not listed in the ACPI name space at
			 * all. Try to get acpi handle of parent pci bus.
			 */
			struct pci_bus *pbus;
			for (pbus = pci_dev->bus; pbus; pbus = pbus->parent) {
				handle = acpi_pci_get_bridge_handle(pbus);
				if (handle)
					break;
			}
		}
		if (handle) {
			acpi_status status;

			do {
				unsigned long long pxm;

				status = acpi_evaluate_integer(handle, "_PXM",
							       NULL, &pxm);
				if (ACPI_SUCCESS(status)) {
					add->optarr[0] = pxm;
					add->flags |= XEN_PCI_DEV_PXM;
					break;
				}
				status = acpi_get_parent(handle, &handle);
			} while (ACPI_SUCCESS(status));
		}
#endif /* CONFIG_ACPI */

		r = HYPERVISOR_physdev_op(PHYSDEVOP_pci_device_add, add);
		if (r != -ENOSYS)
			return r;
		pci_seg_supported = false;
	}

	if (pci_domain_nr(pci_dev->bus))
		r = -ENOSYS;
#ifdef CONFIG_PCI_IOV
	else if (pci_dev->is_virtfn) {
		struct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_virtfn 	= 1,
			.physfn.bus	= physfn->bus->number,
			.physfn.devfn	= physfn->devfn,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	}
#endif
	else if (pci_ari_enabled(pci_dev->bus) && PCI_SLOT(pci_dev->devfn)) {
		struct physdev_manage_pci_ext manage_pci_ext = {
			.bus		= pci_dev->bus->number,
			.devfn		= pci_dev->devfn,
			.is_extfn	= 1,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add_ext,
			&manage_pci_ext);
	} else {
		struct physdev_manage_pci manage_pci = {
			.bus	= pci_dev->bus->number,
			.devfn	= pci_dev->devfn,
		};

		r = HYPERVISOR_physdev_op(PHYSDEVOP_manage_pci_add,
			&manage_pci);
	}

	return r;
}