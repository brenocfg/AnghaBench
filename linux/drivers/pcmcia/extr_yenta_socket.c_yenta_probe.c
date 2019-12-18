#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * parent; } ;
struct TYPE_7__ {int features; int map_size; struct pci_dev* cb_dev; int /*<<< orphan*/  owner; struct yenta_socket* driver_data; TYPE_1__ dev; int /*<<< orphan*/ * resource_ops; int /*<<< orphan*/ * ops; } ;
struct yenta_socket {int /*<<< orphan*/  base; int /*<<< orphan*/  poll_timer; scalar_t__ cb_irq; TYPE_2__ socket; TYPE_4__* type; struct pci_dev* dev; } ;
struct pci_device_id {size_t driver_data; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  subordinate; scalar_t__ irq; int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; } ;
struct TYPE_8__ {int (* override ) (struct yenta_socket*) ;} ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_4__*) ; 
 size_t CARDBUS_TYPE_DEFAULT ; 
 int /*<<< orphan*/  CB_SOCKET_MASK ; 
 int /*<<< orphan*/  CB_SOCKET_STATE ; 
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int SS_CAP_CARDBUS ; 
 int SS_CAP_PAGE_REGS ; 
 int SS_CAP_PCCARD ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_4__* cardbus_type ; 
 int /*<<< orphan*/  cb_readl (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cb_writel (struct yenta_socket*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_yenta_registers ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct yenta_socket*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_interrupts ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (struct yenta_socket*) ; 
 struct yenta_socket* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pccard_nonstatic_ops ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct yenta_socket*) ; 
 int pcmcia_register_socket (TYPE_2__*) ; 
 int /*<<< orphan*/  pcmcia_unregister_socket (TYPE_2__*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct yenta_socket*) ; 
 int stub1 (struct yenta_socket*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yenta_allocate_resources (struct yenta_socket*) ; 
 int /*<<< orphan*/  yenta_config_init (struct yenta_socket*) ; 
 int /*<<< orphan*/  yenta_fixup_parent_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yenta_free_resources (struct yenta_socket*) ; 
 int /*<<< orphan*/  yenta_get_socket_capabilities (struct yenta_socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yenta_interrogate (struct yenta_socket*) ; 
 int /*<<< orphan*/  yenta_interrupt ; 
 int /*<<< orphan*/  yenta_interrupt_wrapper ; 
 int /*<<< orphan*/  yenta_socket_operations ; 

__attribute__((used)) static int yenta_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct yenta_socket *socket;
	int ret;

	/*
	 * If we failed to assign proper bus numbers for this cardbus
	 * controller during PCI probe, its subordinate pci_bus is NULL.
	 * Bail out if so.
	 */
	if (!dev->subordinate) {
		dev_err(&dev->dev, "no bus associated! (try 'pci=assign-busses')\n");
		return -ENODEV;
	}

	socket = kzalloc(sizeof(struct yenta_socket), GFP_KERNEL);
	if (!socket)
		return -ENOMEM;

	/* prepare pcmcia_socket */
	socket->socket.ops = &yenta_socket_operations;
	socket->socket.resource_ops = &pccard_nonstatic_ops;
	socket->socket.dev.parent = &dev->dev;
	socket->socket.driver_data = socket;
	socket->socket.owner = THIS_MODULE;
	socket->socket.features = SS_CAP_PAGE_REGS | SS_CAP_PCCARD;
	socket->socket.map_size = 0x1000;
	socket->socket.cb_dev = dev;

	/* prepare struct yenta_socket */
	socket->dev = dev;
	pci_set_drvdata(dev, socket);

	/*
	 * Do some basic sanity checking..
	 */
	if (pci_enable_device(dev)) {
		ret = -EBUSY;
		goto free;
	}

	ret = pci_request_regions(dev, "yenta_socket");
	if (ret)
		goto disable;

	if (!pci_resource_start(dev, 0)) {
		dev_err(&dev->dev, "No cardbus resource!\n");
		ret = -ENODEV;
		goto release;
	}

	/*
	 * Ok, start setup.. Map the cardbus registers,
	 * and request the IRQ.
	 */
	socket->base = ioremap(pci_resource_start(dev, 0), 0x1000);
	if (!socket->base) {
		ret = -ENOMEM;
		goto release;
	}

	/*
	 * report the subsystem vendor and device for help debugging
	 * the irq stuff...
	 */
	dev_info(&dev->dev, "CardBus bridge found [%04x:%04x]\n",
		 dev->subsystem_vendor, dev->subsystem_device);

	yenta_config_init(socket);

	/* Disable all events */
	cb_writel(socket, CB_SOCKET_MASK, 0x0);

	/* Set up the bridge regions.. */
	yenta_allocate_resources(socket);

	socket->cb_irq = dev->irq;

	/* Do we have special options for the device? */
	if (id->driver_data != CARDBUS_TYPE_DEFAULT &&
	    id->driver_data < ARRAY_SIZE(cardbus_type)) {
		socket->type = &cardbus_type[id->driver_data];

		ret = socket->type->override(socket);
		if (ret < 0)
			goto unmap;
	}

	/* We must finish initialization here */

	if (!socket->cb_irq || request_irq(socket->cb_irq, yenta_interrupt, IRQF_SHARED, "yenta", socket)) {
		/* No IRQ or request_irq failed. Poll */
		socket->cb_irq = 0; /* But zero is a valid IRQ number. */
		timer_setup(&socket->poll_timer, yenta_interrupt_wrapper, 0);
		mod_timer(&socket->poll_timer, jiffies + HZ);
		dev_info(&dev->dev,
			 "no PCI IRQ, CardBus support disabled for this socket.\n");
		dev_info(&dev->dev,
			 "check your BIOS CardBus, BIOS IRQ or ACPI settings.\n");
	} else {
		socket->socket.features |= SS_CAP_CARDBUS;
	}

	/* Figure out what the dang thing can do for the PCMCIA layer... */
	yenta_interrogate(socket);
	yenta_get_socket_capabilities(socket, isa_interrupts);
	dev_info(&dev->dev, "Socket status: %08x\n",
		 cb_readl(socket, CB_SOCKET_STATE));

	yenta_fixup_parent_bridge(dev->subordinate);

	/* Register it with the pcmcia layer.. */
	ret = pcmcia_register_socket(&socket->socket);
	if (ret)
		goto free_irq;

	/* Add the yenta register attributes */
	ret = device_create_file(&dev->dev, &dev_attr_yenta_registers);
	if (ret)
		goto unregister_socket;

	return ret;

	/* error path... */
 unregister_socket:
	pcmcia_unregister_socket(&socket->socket);
 free_irq:
	if (socket->cb_irq)
		free_irq(socket->cb_irq, socket);
	else
		del_timer_sync(&socket->poll_timer);
 unmap:
	iounmap(socket->base);
	yenta_free_resources(socket);
 release:
	pci_release_regions(dev);
 disable:
	pci_disable_device(dev);
 free:
	pci_set_drvdata(dev, NULL);
	kfree(socket);
	return ret;
}