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
struct pci_device_id {size_t driver_data; int /*<<< orphan*/  device; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mfd_cell {int dummy; } ;
struct lpc_sch_info {int irq_gpio; int /*<<< orphan*/  io_size_wdt; int /*<<< orphan*/  io_size_gpio; int /*<<< orphan*/  io_size_smbus; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GPIOBASE ; 
 int /*<<< orphan*/  SMBASE ; 
 int /*<<< orphan*/  WDTBASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int lpc_sch_populate_cell (struct pci_dev*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct mfd_cell*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mfd_cell*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct lpc_sch_info* sch_chipset_info ; 

__attribute__((used)) static int lpc_sch_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct mfd_cell lpc_sch_cells[3];
	struct lpc_sch_info *info = &sch_chipset_info[id->driver_data];
	unsigned int cells = 0;
	int ret;

	ret = lpc_sch_populate_cell(dev, SMBASE, "isch_smbus",
				    info->io_size_smbus, -1,
				    id->device, &lpc_sch_cells[cells]);
	if (ret < 0)
		return ret;
	if (ret == 0)
		cells++;

	ret = lpc_sch_populate_cell(dev, GPIOBASE, "sch_gpio",
				    info->io_size_gpio, info->irq_gpio,
				    id->device, &lpc_sch_cells[cells]);
	if (ret < 0)
		return ret;
	if (ret == 0)
		cells++;

	ret = lpc_sch_populate_cell(dev, WDTBASE, "ie6xx_wdt",
				    info->io_size_wdt, -1,
				    id->device, &lpc_sch_cells[cells]);
	if (ret < 0)
		return ret;
	if (ret == 0)
		cells++;

	if (cells == 0) {
		dev_err(&dev->dev, "All decode registers disabled.\n");
		return -ENODEV;
	}

	return mfd_add_devices(&dev->dev, 0, lpc_sch_cells, cells, NULL, 0, NULL);
}