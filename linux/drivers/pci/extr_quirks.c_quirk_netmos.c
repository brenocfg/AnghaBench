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
struct pci_dev {int subsystem_device; int device; int class; int /*<<< orphan*/  subsystem_vendor; } ;

/* Variables and functions */
 int PCI_CLASS_COMMUNICATION_OTHER ; 
#define  PCI_DEVICE_ID_NETMOS_9735 132 
#define  PCI_DEVICE_ID_NETMOS_9745 131 
#define  PCI_DEVICE_ID_NETMOS_9835 130 
#define  PCI_DEVICE_ID_NETMOS_9845 129 
#define  PCI_DEVICE_ID_NETMOS_9855 128 
 int /*<<< orphan*/  PCI_VENDOR_ID_IBM ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,unsigned int,unsigned int) ; 

__attribute__((used)) static void quirk_netmos(struct pci_dev *dev)
{
	unsigned int num_parallel = (dev->subsystem_device & 0xf0) >> 4;
	unsigned int num_serial = dev->subsystem_device & 0xf;

	/*
	 * These Netmos parts are multiport serial devices with optional
	 * parallel ports.  Even when parallel ports are present, they
	 * are identified as class SERIAL, which means the serial driver
	 * will claim them.  To prevent this, mark them as class OTHER.
	 * These combo devices should be claimed by parport_serial.
	 *
	 * The subdevice ID is of the form 0x00PS, where <P> is the number
	 * of parallel ports and <S> is the number of serial ports.
	 */
	switch (dev->device) {
	case PCI_DEVICE_ID_NETMOS_9835:
		/* Well, this rule doesn't hold for the following 9835 device */
		if (dev->subsystem_vendor == PCI_VENDOR_ID_IBM &&
				dev->subsystem_device == 0x0299)
			return;
		/* else, fall through */
	case PCI_DEVICE_ID_NETMOS_9735:
	case PCI_DEVICE_ID_NETMOS_9745:
	case PCI_DEVICE_ID_NETMOS_9845:
	case PCI_DEVICE_ID_NETMOS_9855:
		if (num_parallel) {
			pci_info(dev, "Netmos %04x (%u parallel, %u serial); changing class SERIAL to OTHER (use parport_serial)\n",
				dev->device, num_parallel, num_serial);
			dev->class = (PCI_CLASS_COMMUNICATION_OTHER << 8) |
			    (dev->class & 0xff);
		}
	}
}