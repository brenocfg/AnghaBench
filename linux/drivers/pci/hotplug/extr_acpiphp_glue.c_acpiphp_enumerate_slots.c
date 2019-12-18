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
struct pci_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  self; int /*<<< orphan*/  bridge; } ;
struct acpiphp_root_context {int /*<<< orphan*/  hp; struct acpiphp_bridge* root_bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct acpiphp_context {TYPE_1__ func; struct acpiphp_bridge* bridge; } ;
struct acpiphp_bridge {int /*<<< orphan*/  pci_dev; int /*<<< orphan*/  list; struct acpiphp_context* context; struct pci_bus* pci_bus; int /*<<< orphan*/  ref; int /*<<< orphan*/  slots; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  acpi_lock_hp_context () ; 
 int /*<<< orphan*/  acpi_set_hp_context (struct acpi_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_unlock_hp_context () ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpiphp_bridge*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpiphp_add_context ; 
 scalar_t__ acpiphp_disabled ; 
 struct acpiphp_context* acpiphp_get_context (struct acpi_device*) ; 
 int /*<<< orphan*/  bridge_list ; 
 int /*<<< orphan*/  bridge_mutex ; 
 int /*<<< orphan*/  cleanup_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  get_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_is_root_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  put_bridge (struct acpiphp_bridge*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void acpiphp_enumerate_slots(struct pci_bus *bus)
{
	struct acpiphp_bridge *bridge;
	struct acpi_device *adev;
	acpi_handle handle;
	acpi_status status;

	if (acpiphp_disabled)
		return;

	adev = ACPI_COMPANION(bus->bridge);
	if (!adev)
		return;

	handle = adev->handle;
	bridge = kzalloc(sizeof(struct acpiphp_bridge), GFP_KERNEL);
	if (!bridge)
		return;

	INIT_LIST_HEAD(&bridge->slots);
	kref_init(&bridge->ref);
	bridge->pci_dev = pci_dev_get(bus->self);
	bridge->pci_bus = bus;

	/*
	 * Grab a ref to the subordinate PCI bus in case the bus is
	 * removed via PCI core logical hotplug. The ref pins the bus
	 * (which we access during module unload).
	 */
	get_device(&bus->dev);

	acpi_lock_hp_context();
	if (pci_is_root_bus(bridge->pci_bus)) {
		struct acpiphp_root_context *root_context;

		root_context = kzalloc(sizeof(*root_context), GFP_KERNEL);
		if (!root_context)
			goto err;

		root_context->root_bridge = bridge;
		acpi_set_hp_context(adev, &root_context->hp);
	} else {
		struct acpiphp_context *context;

		/*
		 * This bridge should have been registered as a hotplug function
		 * under its parent, so the context should be there, unless the
		 * parent is going to be handled by pciehp, in which case this
		 * bridge is not interesting to us either.
		 */
		context = acpiphp_get_context(adev);
		if (!context)
			goto err;

		bridge->context = context;
		context->bridge = bridge;
		/* Get a reference to the parent bridge. */
		get_bridge(context->func.parent);
	}
	acpi_unlock_hp_context();

	/* Must be added to the list prior to calling acpiphp_add_context(). */
	mutex_lock(&bridge_mutex);
	list_add(&bridge->list, &bridge_list);
	mutex_unlock(&bridge_mutex);

	/* register all slot objects under this bridge */
	status = acpi_walk_namespace(ACPI_TYPE_DEVICE, handle, 1,
				     acpiphp_add_context, NULL, bridge, NULL);
	if (ACPI_FAILURE(status)) {
		acpi_handle_err(handle, "failed to register slots\n");
		cleanup_bridge(bridge);
		put_bridge(bridge);
	}
	return;

 err:
	acpi_unlock_hp_context();
	put_device(&bus->dev);
	pci_dev_put(bridge->pci_dev);
	kfree(bridge);
}