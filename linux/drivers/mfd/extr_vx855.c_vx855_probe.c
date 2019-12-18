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
typedef  int u16 ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  VX855_CFG_PMIO_OFFSET ; 
 scalar_t__ VX855_PMIO_R_GPI ; 
 scalar_t__ VX855_PMIO_R_GPO ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int mfd_add_devices (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vx855_cells ; 
 TYPE_1__* vx855_gpio_resources ; 

__attribute__((used)) static int vx855_probe(struct pci_dev *pdev,
				 const struct pci_device_id *id)
{
	int ret;
	u16 gpio_io_offset;

	ret = pci_enable_device(pdev);
	if (ret)
		return -ENODEV;

	pci_read_config_word(pdev, VX855_CFG_PMIO_OFFSET, &gpio_io_offset);
	if (!gpio_io_offset) {
		dev_warn(&pdev->dev,
			"BIOS did not assign PMIO base offset?!?\n");
		ret = -ENODEV;
		goto out;
	}

	/* mask out the lowest seven bits, as they are always zero, but
	 * hardware returns them as 0x01 */
	gpio_io_offset &= 0xff80;

	/* As the region identified here includes many non-GPIO things, we
	 * only work with the specific registers that concern us. */
	vx855_gpio_resources[0].start = gpio_io_offset + VX855_PMIO_R_GPI;
	vx855_gpio_resources[0].end = vx855_gpio_resources[0].start + 3;
	vx855_gpio_resources[1].start = gpio_io_offset + VX855_PMIO_R_GPO;
	vx855_gpio_resources[1].end = vx855_gpio_resources[1].start + 3;

	ret = mfd_add_devices(&pdev->dev, -1, vx855_cells, ARRAY_SIZE(vx855_cells),
			NULL, 0, NULL);

	/* we always return -ENODEV here in order to enable other
	 * drivers like old, not-yet-platform_device ported i2c-viapro */
	return -ENODEV;
out:
	pci_disable_device(pdev);
	return ret;
}