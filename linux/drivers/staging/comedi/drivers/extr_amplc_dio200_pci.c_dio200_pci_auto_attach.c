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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct dio200_board {unsigned int mainbar; scalar_t__ is_pcie; int /*<<< orphan*/  name; } ;
struct comedi_device {int /*<<< orphan*/  iobase; int /*<<< orphan*/  class_dev; int /*<<< orphan*/  mmio; int /*<<< orphan*/  board_name; TYPE_1__* driver; struct dio200_board const* board_ptr; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver_name; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (struct dio200_board*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int amplc_dio200_common_attach (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int comedi_pci_enable (struct comedi_device*) ; 
 struct pci_dev* comedi_to_pci_dev (struct comedi_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dio200_board* dio200_pci_boards ; 
 int dio200_pcie_board_setup (struct comedi_device*) ; 
 int /*<<< orphan*/  pci_ioremap_bar (struct pci_dev*,unsigned int) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int pci_resource_flags (struct pci_dev*,unsigned int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,unsigned int) ; 

__attribute__((used)) static int dio200_pci_auto_attach(struct comedi_device *dev,
				  unsigned long context_model)
{
	struct pci_dev *pci_dev = comedi_to_pci_dev(dev);
	const struct dio200_board *board = NULL;
	unsigned int bar;
	int ret;

	if (context_model < ARRAY_SIZE(dio200_pci_boards))
		board = &dio200_pci_boards[context_model];
	if (!board)
		return -EINVAL;
	dev->board_ptr = board;
	dev->board_name = board->name;

	dev_info(dev->class_dev, "%s: attach pci %s (%s)\n",
		 dev->driver->driver_name, pci_name(pci_dev), dev->board_name);

	ret = comedi_pci_enable(dev);
	if (ret)
		return ret;

	bar = board->mainbar;
	if (pci_resource_flags(pci_dev, bar) & IORESOURCE_MEM) {
		dev->mmio = pci_ioremap_bar(pci_dev, bar);
		if (!dev->mmio) {
			dev_err(dev->class_dev,
				"error! cannot remap registers\n");
			return -ENOMEM;
		}
	} else {
		dev->iobase = pci_resource_start(pci_dev, bar);
	}

	if (board->is_pcie) {
		ret = dio200_pcie_board_setup(dev);
		if (ret < 0)
			return ret;
	}

	return amplc_dio200_common_attach(dev, pci_dev->irq, IRQF_SHARED);
}