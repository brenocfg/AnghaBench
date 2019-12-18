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
struct pci_device_id {int dummy; } ;
struct pci_dev {unsigned int irq; int /*<<< orphan*/  dev; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;
struct AdapterCtlBlk {struct pci_dev* dev; struct Scsi_Host* scsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_0 ; 
 int ENODEV ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned long PCI_BASE_ADDRESS_IO_MASK ; 
 scalar_t__ adapter_init (struct AdapterCtlBlk*,unsigned long,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  adapter_uninit (struct AdapterCtlBlk*) ; 
 int /*<<< orphan*/  banner_display () ; 
 int /*<<< orphan*/  dc395x_driver_template ; 
 int /*<<< orphan*/  dprintkdbg (int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 unsigned int pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct Scsi_Host*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 scalar_t__ scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_scan_host (struct Scsi_Host*) ; 

__attribute__((used)) static int dc395x_init_one(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct Scsi_Host *scsi_host = NULL;
	struct AdapterCtlBlk *acb = NULL;
	unsigned long io_port_base;
	unsigned int io_port_len;
	unsigned int irq;
	
	dprintkdbg(DBG_0, "Init one instance (%s)\n", pci_name(dev));
	banner_display();

	if (pci_enable_device(dev))
	{
		dprintkl(KERN_INFO, "PCI Enable device failed.\n");
		return -ENODEV;
	}
	io_port_base = pci_resource_start(dev, 0) & PCI_BASE_ADDRESS_IO_MASK;
	io_port_len = pci_resource_len(dev, 0);
	irq = dev->irq;
	dprintkdbg(DBG_0, "IO_PORT=0x%04lx, IRQ=0x%x\n", io_port_base, dev->irq);

	/* allocate scsi host information (includes out adapter) */
	scsi_host = scsi_host_alloc(&dc395x_driver_template,
				    sizeof(struct AdapterCtlBlk));
	if (!scsi_host) {
		dprintkl(KERN_INFO, "scsi_host_alloc failed\n");
		goto fail;
	}
 	acb = (struct AdapterCtlBlk*)scsi_host->hostdata;
 	acb->scsi_host = scsi_host;
 	acb->dev = dev;

	/* initialise the adapter and everything we need */
 	if (adapter_init(acb, io_port_base, io_port_len, irq)) {
		dprintkl(KERN_INFO, "adapter init failed\n");
		goto fail;
	}

	pci_set_master(dev);

	/* get the scsi mid level to scan for new devices on the bus */
	if (scsi_add_host(scsi_host, &dev->dev)) {
		dprintkl(KERN_ERR, "scsi_add_host failed\n");
		goto fail;
	}
	pci_set_drvdata(dev, scsi_host);
	scsi_scan_host(scsi_host);
        	
	return 0;

fail:
	if (acb != NULL)
		adapter_uninit(acb);
	if (scsi_host != NULL)
		scsi_host_put(scsi_host);
	pci_disable_device(dev);
	return -ENODEV;
}