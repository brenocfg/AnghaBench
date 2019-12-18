#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct resource {void* flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  parent; } ;
struct pci_dev {int hdr_type; int multifunction; int dma_mask; int revision; int class; int subsystem_vendor; int subsystem_device; int transparent; TYPE_1__* bus; struct resource* resource; int /*<<< orphan*/  broken_intx_masking; scalar_t__ non_compliant_bars; int /*<<< orphan*/  current_state; int /*<<< orphan*/  cfg_size; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; int /*<<< orphan*/  devfn; TYPE_3__ dev; int /*<<< orphan*/  error_state; int /*<<< orphan*/  sysdata; } ;
struct pci_bus_region {int start; int end; } ;
struct TYPE_4__ {int /*<<< orphan*/  number; int /*<<< orphan*/  bridge; int /*<<< orphan*/  sysdata; } ;

/* Variables and functions */
 int EIO ; 
 void* LEGACY_IO_RESOURCE ; 
 int /*<<< orphan*/  PCI_CAP_ID_SSVID ; 
 int /*<<< orphan*/  PCI_CB_SUBSYSTEM_ID ; 
 int /*<<< orphan*/  PCI_CB_SUBSYSTEM_VENDOR_ID ; 
 int PCI_CLASS_BRIDGE_CARDBUS ; 
 int PCI_CLASS_BRIDGE_PCI ; 
 int PCI_CLASS_NOT_DEFINED ; 
 int /*<<< orphan*/  PCI_CLASS_PROG ; 
 int PCI_CLASS_STORAGE_IDE ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
#define  PCI_HEADER_TYPE_BRIDGE 130 
#define  PCI_HEADER_TYPE_CARDBUS 129 
#define  PCI_HEADER_TYPE_NORMAL 128 
 int /*<<< orphan*/  PCI_ROM_ADDRESS ; 
 int /*<<< orphan*/  PCI_ROM_ADDRESS1 ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SSVID_DEVICE_ID ; 
 int /*<<< orphan*/  PCI_SSVID_VENDOR_ID ; 
 int /*<<< orphan*/  PCI_UNKNOWN ; 
 int /*<<< orphan*/  dev_set_name (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  early_dump_pci_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/  pci_cfg_space_size (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_channel_io_normal ; 
 int pci_class (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_assign_slot (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 scalar_t__ pci_early_dump ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int,...) ; 
 int pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_fixup_device (int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  pci_fixup_early ; 
 int pci_hdr_type (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,...) ; 
 int /*<<< orphan*/  pci_intx_mask_broken (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_bases (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_bridge_windows (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_read_irq (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_subsystem_ids (struct pci_dev*,int*,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcibios_bus_to_resource (TYPE_1__*,struct resource*,struct pci_bus_region*) ; 
 int /*<<< orphan*/  set_pcie_hotplug_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  set_pcie_port_type (struct pci_dev*) ; 
 int /*<<< orphan*/  set_pcie_thunderbolt (struct pci_dev*) ; 
 int /*<<< orphan*/  set_pcie_untrusted (struct pci_dev*) ; 

int pci_setup_device(struct pci_dev *dev)
{
	u32 class;
	u16 cmd;
	u8 hdr_type;
	int pos = 0;
	struct pci_bus_region region;
	struct resource *res;

	hdr_type = pci_hdr_type(dev);

	dev->sysdata = dev->bus->sysdata;
	dev->dev.parent = dev->bus->bridge;
	dev->dev.bus = &pci_bus_type;
	dev->hdr_type = hdr_type & 0x7f;
	dev->multifunction = !!(hdr_type & 0x80);
	dev->error_state = pci_channel_io_normal;
	set_pcie_port_type(dev);

	pci_dev_assign_slot(dev);

	/*
	 * Assume 32-bit PCI; let 64-bit PCI cards (which are far rarer)
	 * set this higher, assuming the system even supports it.
	 */
	dev->dma_mask = 0xffffffff;

	dev_set_name(&dev->dev, "%04x:%02x:%02x.%d", pci_domain_nr(dev->bus),
		     dev->bus->number, PCI_SLOT(dev->devfn),
		     PCI_FUNC(dev->devfn));

	class = pci_class(dev);

	dev->revision = class & 0xff;
	dev->class = class >> 8;		    /* upper 3 bytes */

	pci_info(dev, "[%04x:%04x] type %02x class %#08x\n",
		   dev->vendor, dev->device, dev->hdr_type, dev->class);

	if (pci_early_dump)
		early_dump_pci_device(dev);

	/* Need to have dev->class ready */
	dev->cfg_size = pci_cfg_space_size(dev);

	/* Need to have dev->cfg_size ready */
	set_pcie_thunderbolt(dev);

	set_pcie_untrusted(dev);

	/* "Unknown power state" */
	dev->current_state = PCI_UNKNOWN;

	/* Early fixups, before probing the BARs */
	pci_fixup_device(pci_fixup_early, dev);

	/* Device class may be changed after fixup */
	class = dev->class >> 8;

	if (dev->non_compliant_bars) {
		pci_read_config_word(dev, PCI_COMMAND, &cmd);
		if (cmd & (PCI_COMMAND_IO | PCI_COMMAND_MEMORY)) {
			pci_info(dev, "device has non-compliant BARs; disabling IO/MEM decoding\n");
			cmd &= ~PCI_COMMAND_IO;
			cmd &= ~PCI_COMMAND_MEMORY;
			pci_write_config_word(dev, PCI_COMMAND, cmd);
		}
	}

	dev->broken_intx_masking = pci_intx_mask_broken(dev);

	switch (dev->hdr_type) {		    /* header type */
	case PCI_HEADER_TYPE_NORMAL:		    /* standard header */
		if (class == PCI_CLASS_BRIDGE_PCI)
			goto bad;
		pci_read_irq(dev);
		pci_read_bases(dev, 6, PCI_ROM_ADDRESS);

		pci_subsystem_ids(dev, &dev->subsystem_vendor, &dev->subsystem_device);

		/*
		 * Do the ugly legacy mode stuff here rather than broken chip
		 * quirk code. Legacy mode ATA controllers have fixed
		 * addresses. These are not always echoed in BAR0-3, and
		 * BAR0-3 in a few cases contain junk!
		 */
		if (class == PCI_CLASS_STORAGE_IDE) {
			u8 progif;
			pci_read_config_byte(dev, PCI_CLASS_PROG, &progif);
			if ((progif & 1) == 0) {
				region.start = 0x1F0;
				region.end = 0x1F7;
				res = &dev->resource[0];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x10: %pR\n",
					 res);
				region.start = 0x3F6;
				region.end = 0x3F6;
				res = &dev->resource[1];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x14: %pR\n",
					 res);
			}
			if ((progif & 4) == 0) {
				region.start = 0x170;
				region.end = 0x177;
				res = &dev->resource[2];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x18: %pR\n",
					 res);
				region.start = 0x376;
				region.end = 0x376;
				res = &dev->resource[3];
				res->flags = LEGACY_IO_RESOURCE;
				pcibios_bus_to_resource(dev->bus, res, &region);
				pci_info(dev, "legacy IDE quirk: reg 0x1c: %pR\n",
					 res);
			}
		}
		break;

	case PCI_HEADER_TYPE_BRIDGE:		    /* bridge header */
		/*
		 * The PCI-to-PCI bridge spec requires that subtractive
		 * decoding (i.e. transparent) bridge must have programming
		 * interface code of 0x01.
		 */
		pci_read_irq(dev);
		dev->transparent = ((dev->class & 0xff) == 1);
		pci_read_bases(dev, 2, PCI_ROM_ADDRESS1);
		pci_read_bridge_windows(dev);
		set_pcie_hotplug_bridge(dev);
		pos = pci_find_capability(dev, PCI_CAP_ID_SSVID);
		if (pos) {
			pci_read_config_word(dev, pos + PCI_SSVID_VENDOR_ID, &dev->subsystem_vendor);
			pci_read_config_word(dev, pos + PCI_SSVID_DEVICE_ID, &dev->subsystem_device);
		}
		break;

	case PCI_HEADER_TYPE_CARDBUS:		    /* CardBus bridge header */
		if (class != PCI_CLASS_BRIDGE_CARDBUS)
			goto bad;
		pci_read_irq(dev);
		pci_read_bases(dev, 1, 0);
		pci_read_config_word(dev, PCI_CB_SUBSYSTEM_VENDOR_ID, &dev->subsystem_vendor);
		pci_read_config_word(dev, PCI_CB_SUBSYSTEM_ID, &dev->subsystem_device);
		break;

	default:				    /* unknown header */
		pci_err(dev, "unknown header type %02x, ignoring device\n",
			dev->hdr_type);
		return -EIO;

	bad:
		pci_err(dev, "ignoring class %#08x (doesn't match header type %02x)\n",
			dev->class, dev->hdr_type);
		dev->class = PCI_CLASS_NOT_DEFINED << 8;
	}

	/* We found a fine healthy device, go go go... */
	return 0;
}