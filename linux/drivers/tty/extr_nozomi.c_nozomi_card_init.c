#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ops; } ;
struct port {int /*<<< orphan*/  fifo_ul; TYPE_1__ port; struct nozomi* dc; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct nozomi {int index_start; int /*<<< orphan*/  base_addr; struct nozomi* send_buf; struct port* port; int /*<<< orphan*/  state; int /*<<< orphan*/  reg_ier; scalar_t__ last_ier; int /*<<< orphan*/  spin_mutex; int /*<<< orphan*/  card_type; struct pci_dev* pdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct nozomi**) ; 
 int /*<<< orphan*/  DBG1 (char*,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIFO_BUFFER_SIZE_UL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int MAX_PORT ; 
 int /*<<< orphan*/  NOZOMI_NAME ; 
 int /*<<< orphan*/  NOZOMI_STATE_ENABLED ; 
 int PORT_MDM ; 
 int PTR_ERR (struct device*) ; 
 scalar_t__ RESET ; 
 int /*<<< orphan*/  SEND_BUF_MAX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  interrupt_handler ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nozomi*) ; 
 struct nozomi* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nozomi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_sysfs_files (struct nozomi*) ; 
 struct nozomi** ndevs ; 
 int /*<<< orphan*/  noz_tty_port_ops ; 
 int /*<<< orphan*/  nozomi_get_card_type (struct nozomi*) ; 
 int /*<<< orphan*/  nozomi_setup_private_data (struct nozomi*) ; 
 int /*<<< orphan*/  ntty_driver ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct nozomi*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nozomi*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_port_init (TYPE_1__*) ; 
 struct device* tty_port_register_device (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writew (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nozomi_card_init(struct pci_dev *pdev,
				      const struct pci_device_id *ent)
{
	int ret;
	struct nozomi *dc = NULL;
	int ndev_idx;
	int i;

	dev_dbg(&pdev->dev, "Init, new card found\n");

	for (ndev_idx = 0; ndev_idx < ARRAY_SIZE(ndevs); ndev_idx++)
		if (!ndevs[ndev_idx])
			break;

	if (ndev_idx >= ARRAY_SIZE(ndevs)) {
		dev_err(&pdev->dev, "no free tty range for this card left\n");
		ret = -EIO;
		goto err;
	}

	dc = kzalloc(sizeof(struct nozomi), GFP_KERNEL);
	if (unlikely(!dc)) {
		dev_err(&pdev->dev, "Could not allocate memory\n");
		ret = -ENOMEM;
		goto err_free;
	}

	dc->pdev = pdev;

	ret = pci_enable_device(dc->pdev);
	if (ret) {
		dev_err(&pdev->dev, "Failed to enable PCI Device\n");
		goto err_free;
	}

	ret = pci_request_regions(dc->pdev, NOZOMI_NAME);
	if (ret) {
		dev_err(&pdev->dev, "I/O address 0x%04x already in use\n",
			(int) /* nozomi_private.io_addr */ 0);
		goto err_disable_device;
	}

	/* Find out what card type it is */
	nozomi_get_card_type(dc);

	dc->base_addr = pci_iomap(dc->pdev, 0, dc->card_type);
	if (!dc->base_addr) {
		dev_err(&pdev->dev, "Unable to map card MMIO\n");
		ret = -ENODEV;
		goto err_rel_regs;
	}

	dc->send_buf = kmalloc(SEND_BUF_MAX, GFP_KERNEL);
	if (!dc->send_buf) {
		dev_err(&pdev->dev, "Could not allocate send buffer?\n");
		ret = -ENOMEM;
		goto err_free_sbuf;
	}

	for (i = PORT_MDM; i < MAX_PORT; i++) {
		if (kfifo_alloc(&dc->port[i].fifo_ul, FIFO_BUFFER_SIZE_UL,
					GFP_KERNEL)) {
			dev_err(&pdev->dev,
					"Could not allocate kfifo buffer\n");
			ret = -ENOMEM;
			goto err_free_kfifo;
		}
	}

	spin_lock_init(&dc->spin_mutex);

	nozomi_setup_private_data(dc);

	/* Disable all interrupts */
	dc->last_ier = 0;
	writew(dc->last_ier, dc->reg_ier);

	ret = request_irq(pdev->irq, &interrupt_handler, IRQF_SHARED,
			NOZOMI_NAME, dc);
	if (unlikely(ret)) {
		dev_err(&pdev->dev, "can't request irq %d\n", pdev->irq);
		goto err_free_kfifo;
	}

	DBG1("base_addr: %p", dc->base_addr);

	make_sysfs_files(dc);

	dc->index_start = ndev_idx * MAX_PORT;
	ndevs[ndev_idx] = dc;

	pci_set_drvdata(pdev, dc);

	/* Enable RESET interrupt */
	dc->last_ier = RESET;
	iowrite16(dc->last_ier, dc->reg_ier);

	dc->state = NOZOMI_STATE_ENABLED;

	for (i = 0; i < MAX_PORT; i++) {
		struct device *tty_dev;
		struct port *port = &dc->port[i];
		port->dc = dc;
		tty_port_init(&port->port);
		port->port.ops = &noz_tty_port_ops;
		tty_dev = tty_port_register_device(&port->port, ntty_driver,
				dc->index_start + i, &pdev->dev);

		if (IS_ERR(tty_dev)) {
			ret = PTR_ERR(tty_dev);
			dev_err(&pdev->dev, "Could not allocate tty?\n");
			tty_port_destroy(&port->port);
			goto err_free_tty;
		}
	}

	return 0;

err_free_tty:
	for (i = 0; i < MAX_PORT; ++i) {
		tty_unregister_device(ntty_driver, dc->index_start + i);
		tty_port_destroy(&dc->port[i].port);
	}
err_free_kfifo:
	for (i = 0; i < MAX_PORT; i++)
		kfifo_free(&dc->port[i].fifo_ul);
err_free_sbuf:
	kfree(dc->send_buf);
	iounmap(dc->base_addr);
err_rel_regs:
	pci_release_regions(pdev);
err_disable_device:
	pci_disable_device(pdev);
err_free:
	kfree(dc);
err:
	return ret;
}