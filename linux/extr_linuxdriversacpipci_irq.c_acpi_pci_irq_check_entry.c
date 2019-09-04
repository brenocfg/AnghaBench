#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_2__* bus; } ;
struct TYPE_4__ {int segment; int bus; int device; } ;
struct acpi_prt_entry {int pin; int /*<<< orphan*/  index; TYPE_1__ id; int /*<<< orphan*/  link; } ;
struct acpi_pci_routing_table {int address; int pin; scalar_t__* source; int /*<<< orphan*/  source_index; } ;
typedef  int /*<<< orphan*/  acpi_handle ;
struct TYPE_5__ {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_prt_fixups (struct acpi_prt_entry*,struct acpi_pci_routing_table*) ; 
 struct acpi_prt_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_ari_enabled (TYPE_2__*) ; 
 int pci_domain_nr (TYPE_2__*) ; 
 int /*<<< orphan*/  pin_name (int) ; 

__attribute__((used)) static int acpi_pci_irq_check_entry(acpi_handle handle, struct pci_dev *dev,
				  int pin, struct acpi_pci_routing_table *prt,
				  struct acpi_prt_entry **entry_ptr)
{
	int segment = pci_domain_nr(dev->bus);
	int bus = dev->bus->number;
	int device = pci_ari_enabled(dev->bus) ? 0 : PCI_SLOT(dev->devfn);
	struct acpi_prt_entry *entry;

	if (((prt->address >> 16) & 0xffff) != device ||
	    prt->pin + 1 != pin)
		return -ENODEV;

	entry = kzalloc(sizeof(struct acpi_prt_entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;

	/*
	 * Note that the _PRT uses 0=INTA, 1=INTB, etc, while PCI uses
	 * 1=INTA, 2=INTB.  We use the PCI encoding throughout, so convert
	 * it here.
	 */
	entry->id.segment = segment;
	entry->id.bus = bus;
	entry->id.device = (prt->address >> 16) & 0xFFFF;
	entry->pin = prt->pin + 1;

	do_prt_fixups(entry, prt);

	entry->index = prt->source_index;

	/*
	 * Type 1: Dynamic
	 * ---------------
	 * The 'source' field specifies the PCI interrupt link device used to
	 * configure the IRQ assigned to this slot|dev|pin.  The 'source_index'
	 * indicates which resource descriptor in the resource template (of
	 * the link device) this interrupt is allocated from.
	 * 
	 * NOTE: Don't query the Link Device for IRQ information at this time
	 *       because Link Device enumeration may not have occurred yet
	 *       (e.g. exists somewhere 'below' this _PRT entry in the ACPI
	 *       namespace).
	 */
	if (prt->source[0])
		acpi_get_handle(handle, prt->source, &entry->link);

	/*
	 * Type 2: Static
	 * --------------
	 * The 'source' field is NULL, and the 'source_index' field specifies
	 * the IRQ value, which is hardwired to specific interrupt inputs on
	 * the interrupt controller.
	 */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INFO,
			      "      %04x:%02x:%02x[%c] -> %s[%d]\n",
			      entry->id.segment, entry->id.bus,
			      entry->id.device, pin_name(entry->pin),
			      prt->source, entry->index));

	*entry_ptr = entry;

	return 0;
}