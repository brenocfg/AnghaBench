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
struct service_processor {int number; int /*<<< orphan*/  base_address; int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  devname; int /*<<< orphan*/  dirname; int /*<<< orphan*/  command_queue; int /*<<< orphan*/  lock; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; TYPE_1__* bus; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 char* DRIVER_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IBMASM_NAME_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SYSTEM_STATE_OS_UP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  disable_sp_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_sp_interrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ibmasm_event_buffer_exit (struct service_processor*) ; 
 int ibmasm_event_buffer_init (struct service_processor*) ; 
 int /*<<< orphan*/  ibmasm_free_remote_input_dev (struct service_processor*) ; 
 int /*<<< orphan*/  ibmasm_heartbeat_exit (struct service_processor*) ; 
 int ibmasm_heartbeat_init (struct service_processor*) ; 
 int ibmasm_init_remote_input_dev (struct service_processor*) ; 
 int /*<<< orphan*/  ibmasm_interrupt_handler ; 
 int /*<<< orphan*/  ibmasm_register_uart (struct service_processor*) ; 
 int ibmasm_send_driver_vpd (struct service_processor*) ; 
 int ibmasm_send_os_state (struct service_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibmasmfs_add_sp (struct service_processor*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct service_processor*) ; 
 struct service_processor* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,void*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmasm_init_one(struct pci_dev *pdev, const struct pci_device_id *id)
{
	int result;
	struct service_processor *sp;

	if ((result = pci_enable_device(pdev))) {
		dev_err(&pdev->dev, "Failed to enable PCI device\n");
		return result;
	}
	if ((result = pci_request_regions(pdev, DRIVER_NAME))) {
		dev_err(&pdev->dev, "Failed to allocate PCI resources\n");
		goto error_resources;
	}
	/* vnc client won't work without bus-mastering */
	pci_set_master(pdev);

	sp = kzalloc(sizeof(struct service_processor), GFP_KERNEL);
	if (sp == NULL) {
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		result = -ENOMEM;
		goto error_kmalloc;
	}

	spin_lock_init(&sp->lock);
	INIT_LIST_HEAD(&sp->command_queue);

	pci_set_drvdata(pdev, (void *)sp);
	sp->dev = &pdev->dev;
	sp->number = pdev->bus->number;
	snprintf(sp->dirname, IBMASM_NAME_SIZE, "%d", sp->number);
	snprintf(sp->devname, IBMASM_NAME_SIZE, "%s%d", DRIVER_NAME, sp->number);

	result = ibmasm_event_buffer_init(sp);
	if (result) {
		dev_err(sp->dev, "Failed to allocate event buffer\n");
		goto error_eventbuffer;
	}

	result = ibmasm_heartbeat_init(sp);
	if (result) {
		dev_err(sp->dev, "Failed to allocate heartbeat command\n");
		goto error_heartbeat;
	}

	sp->irq = pdev->irq;
	sp->base_address = pci_ioremap_bar(pdev, 0);
	if (!sp->base_address) {
		dev_err(sp->dev, "Failed to ioremap pci memory\n");
		result =  -ENODEV;
		goto error_ioremap;
	}

	result = request_irq(sp->irq, ibmasm_interrupt_handler, IRQF_SHARED, sp->devname, (void*)sp);
	if (result) {
		dev_err(sp->dev, "Failed to register interrupt handler\n");
		goto error_request_irq;
	}

	enable_sp_interrupts(sp->base_address);

	result = ibmasm_init_remote_input_dev(sp);
	if (result) {
		dev_err(sp->dev, "Failed to initialize remote queue\n");
		goto error_send_message;
	}

	result = ibmasm_send_driver_vpd(sp);
	if (result) {
		dev_err(sp->dev, "Failed to send driver VPD to service processor\n");
		goto error_send_message;
	}
	result = ibmasm_send_os_state(sp, SYSTEM_STATE_OS_UP);
	if (result) {
		dev_err(sp->dev, "Failed to send OS state to service processor\n");
		goto error_send_message;
	}
	ibmasmfs_add_sp(sp);

	ibmasm_register_uart(sp);

	return 0;

error_send_message:
	disable_sp_interrupts(sp->base_address);
	ibmasm_free_remote_input_dev(sp);
	free_irq(sp->irq, (void *)sp);
error_request_irq:
	iounmap(sp->base_address);
error_ioremap:
	ibmasm_heartbeat_exit(sp);
error_heartbeat:
	ibmasm_event_buffer_exit(sp);
error_eventbuffer:
	kfree(sp);
error_kmalloc:
        pci_release_regions(pdev);
error_resources:
        pci_disable_device(pdev);

	return result;
}