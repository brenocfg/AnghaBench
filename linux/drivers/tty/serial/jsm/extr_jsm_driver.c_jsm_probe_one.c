#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int device; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; int /*<<< orphan*/  revision; } ;
struct jsm_board {int maxports; int membase; unsigned int iobase; int bd_uart_offset; int bd_dividend; void* re_map_membase; int /*<<< orphan*/  irq; int /*<<< orphan*/  rev; TYPE_1__* bd_ops; void* membase_end; struct pci_dev* pci_dev; void* iobase_end; int /*<<< orphan*/  bd_intr_lock; int /*<<< orphan*/  boardnum; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  JSM_DRIVER_NAME ; 
#define  PCIE_DEVICE_ID_NEO_4 143 
#define  PCIE_DEVICE_ID_NEO_4RJ45 142 
#define  PCIE_DEVICE_ID_NEO_4_IBM 141 
#define  PCIE_DEVICE_ID_NEO_8 140 
#define  PCIE_DEVICE_ID_NEO_8RJ45 139 
#define  PCI_DEVICE_ID_CLASSIC_4 138 
#define  PCI_DEVICE_ID_CLASSIC_4_422 137 
#define  PCI_DEVICE_ID_CLASSIC_8 136 
#define  PCI_DEVICE_ID_CLASSIC_8_422 135 
#define  PCI_DEVICE_ID_DIGI_NEO_8 134 
#define  PCI_DEVICE_ID_NEO_2DB9 133 
#define  PCI_DEVICE_ID_NEO_2DB9PRI 132 
#define  PCI_DEVICE_ID_NEO_2RJ45 131 
#define  PCI_DEVICE_ID_NEO_2RJ45PRI 130 
#define  PCI_DEVICE_ID_NEO_2_422_485 129 
#define  PCI_DEVICE_ID_NEO_4 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct jsm_board*) ; 
 void* ioremap (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 TYPE_1__ jsm_cls_ops ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,struct pci_dev**,char*) ; 
 TYPE_1__ jsm_neo_ops ; 
 int /*<<< orphan*/  jsm_remove_uart_port (struct jsm_board*) ; 
 int jsm_tty_init (struct jsm_board*) ; 
 int jsm_uart_port_init (struct jsm_board*) ; 
 int /*<<< orphan*/  kfree (struct jsm_board*) ; 
 struct jsm_board* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int pci_request_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 void* pci_resource_end (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 void* pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct jsm_board*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct jsm_board*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jsm_probe_one(struct pci_dev *pdev, const struct pci_device_id *ent)
{
	int rc = 0;
	struct jsm_board *brd;
	static int adapter_count;

	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "Device enable FAILED\n");
		goto out;
	}

	rc = pci_request_regions(pdev, JSM_DRIVER_NAME);
	if (rc) {
		dev_err(&pdev->dev, "pci_request_region FAILED\n");
		goto out_disable_device;
	}

	brd = kzalloc(sizeof(*brd), GFP_KERNEL);
	if (!brd) {
		rc = -ENOMEM;
		goto out_release_regions;
	}

	/* store the info for the board we've found */
	brd->boardnum = adapter_count++;
	brd->pci_dev = pdev;

	switch (pdev->device) {
	case PCI_DEVICE_ID_NEO_2DB9:
	case PCI_DEVICE_ID_NEO_2DB9PRI:
	case PCI_DEVICE_ID_NEO_2RJ45:
	case PCI_DEVICE_ID_NEO_2RJ45PRI:
	case PCI_DEVICE_ID_NEO_2_422_485:
		brd->maxports = 2;
		break;

	case PCI_DEVICE_ID_CLASSIC_4:
	case PCI_DEVICE_ID_CLASSIC_4_422:
	case PCI_DEVICE_ID_NEO_4:
	case PCIE_DEVICE_ID_NEO_4:
	case PCIE_DEVICE_ID_NEO_4RJ45:
	case PCIE_DEVICE_ID_NEO_4_IBM:
		brd->maxports = 4;
		break;

	case PCI_DEVICE_ID_CLASSIC_8:
	case PCI_DEVICE_ID_CLASSIC_8_422:
	case PCI_DEVICE_ID_DIGI_NEO_8:
	case PCIE_DEVICE_ID_NEO_8:
	case PCIE_DEVICE_ID_NEO_8RJ45:
		brd->maxports = 8;
		break;

	default:
		brd->maxports = 1;
		break;
	}

	spin_lock_init(&brd->bd_intr_lock);

	/* store which revision we have */
	brd->rev = pdev->revision;

	brd->irq = pdev->irq;

	switch (pdev->device) {
	case PCI_DEVICE_ID_CLASSIC_4:
	case PCI_DEVICE_ID_CLASSIC_4_422:
	case PCI_DEVICE_ID_CLASSIC_8:
	case PCI_DEVICE_ID_CLASSIC_8_422:

		jsm_dbg(INIT, &brd->pci_dev,
			"jsm_found_board - Classic adapter\n");

		/*
		 * For PCI ClassicBoards
		 * PCI Local Address (.i.e. "resource" number) space
		 * 0	PLX Memory Mapped Config
		 * 1	PLX I/O Mapped Config
		 * 2	I/O Mapped UARTs and Status
		 * 3	Memory Mapped VPD
		 * 4	Memory Mapped UARTs and Status
		 */

		/* Get the PCI Base Address Registers */
		brd->membase = pci_resource_start(pdev, 4);
		brd->membase_end = pci_resource_end(pdev, 4);

		if (brd->membase & 0x1)
			brd->membase &= ~0x3;
		else
			brd->membase &= ~0xF;

		brd->iobase = pci_resource_start(pdev, 1);
		brd->iobase_end = pci_resource_end(pdev, 1);
		brd->iobase = ((unsigned int)(brd->iobase)) & 0xFFFE;

		/* Assign the board_ops struct */
		brd->bd_ops = &jsm_cls_ops;

		brd->bd_uart_offset = 0x8;
		brd->bd_dividend = 921600;

		brd->re_map_membase = ioremap(brd->membase,
						pci_resource_len(pdev, 4));
		if (!brd->re_map_membase) {
			dev_err(&pdev->dev,
				"Card has no PCI Memory resources, failing board.\n");
			rc = -ENOMEM;
			goto out_kfree_brd;
		}

		/*
		 * Enable Local Interrupt 1			(0x1),
		 * Local Interrupt 1 Polarity Active high	(0x2),
		 * Enable PCI interrupt				(0x43)
		 */
		outb(0x43, brd->iobase + 0x4c);

		break;

	case PCI_DEVICE_ID_NEO_2DB9:
	case PCI_DEVICE_ID_NEO_2DB9PRI:
	case PCI_DEVICE_ID_NEO_2RJ45:
	case PCI_DEVICE_ID_NEO_2RJ45PRI:
	case PCI_DEVICE_ID_NEO_2_422_485:
	case PCI_DEVICE_ID_NEO_4:
	case PCIE_DEVICE_ID_NEO_4:
	case PCIE_DEVICE_ID_NEO_4RJ45:
	case PCIE_DEVICE_ID_NEO_4_IBM:
	case PCI_DEVICE_ID_DIGI_NEO_8:
	case PCIE_DEVICE_ID_NEO_8:
	case PCIE_DEVICE_ID_NEO_8RJ45:

		jsm_dbg(INIT, &brd->pci_dev, "jsm_found_board - NEO adapter\n");

		/* get the PCI Base Address Registers */
		brd->membase	= pci_resource_start(pdev, 0);
		brd->membase_end = pci_resource_end(pdev, 0);

		if (brd->membase & 1)
			brd->membase &= ~0x3;
		else
			brd->membase &= ~0xF;

		/* Assign the board_ops struct */
		brd->bd_ops = &jsm_neo_ops;

		brd->bd_uart_offset = 0x200;
		brd->bd_dividend = 921600;

		brd->re_map_membase = ioremap(brd->membase,
						pci_resource_len(pdev, 0));
		if (!brd->re_map_membase) {
			dev_err(&pdev->dev,
				"Card has no PCI Memory resources, failing board.\n");
			rc = -ENOMEM;
			goto out_kfree_brd;
		}

		break;
	default:
		return -ENXIO;
	}

	rc = request_irq(brd->irq, brd->bd_ops->intr, IRQF_SHARED, "JSM", brd);
	if (rc) {
		dev_warn(&pdev->dev, "Failed to hook IRQ %d\n", brd->irq);
		goto out_iounmap;
	}

	rc = jsm_tty_init(brd);
	if (rc < 0) {
		dev_err(&pdev->dev, "Can't init tty devices (%d)\n", rc);
		rc = -ENXIO;
		goto out_free_irq;
	}

	rc = jsm_uart_port_init(brd);
	if (rc < 0) {
		/* XXX: leaking all resources from jsm_tty_init here! */
		dev_err(&pdev->dev, "Can't init uart port (%d)\n", rc);
		rc = -ENXIO;
		goto out_free_irq;
	}

	/* Log the information about the board */
	dev_info(&pdev->dev, "board %d: Digi Classic/Neo (rev %d), irq %d\n",
			adapter_count, brd->rev, brd->irq);

	pci_set_drvdata(pdev, brd);
	pci_save_state(pdev);

	return 0;
 out_free_irq:
	jsm_remove_uart_port(brd);
	free_irq(brd->irq, brd);
 out_iounmap:
	iounmap(brd->re_map_membase);
 out_kfree_brd:
	kfree(brd);
 out_release_regions:
	pci_release_regions(pdev);
 out_disable_device:
	pci_disable_device(pdev);
 out:
	return rc;
}