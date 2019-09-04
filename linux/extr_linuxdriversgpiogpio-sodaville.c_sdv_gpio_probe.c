#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ngpio; } ;
struct sdv_gpio_chip_data {scalar_t__ gpio_pub_base; TYPE_1__ chip; } ;
struct pci_device_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct pci_dev {TYPE_2__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GPINR ; 
 int /*<<< orphan*/  GPIO_BAR ; 
 scalar_t__ GPMUXCTL ; 
 scalar_t__ GPOER ; 
 scalar_t__ GPOUTR ; 
 int /*<<< orphan*/  SDV_NUM_PUB_GPIOS ; 
 int bgpio_init (TYPE_1__*,TYPE_2__*,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 int gpiochip_add_data (TYPE_1__*,struct sdv_gpio_chip_data*) ; 
 scalar_t__ ioremap (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sdv_gpio_chip_data*) ; 
 struct sdv_gpio_chip_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* of_get_property (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_read_number (void const*,int) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int pci_enable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int pci_request_region (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int /*<<< orphan*/ ) ; 
 unsigned long pci_resource_start (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct sdv_gpio_chip_data*) ; 
 int sdv_register_irqsupport (struct sdv_gpio_chip_data*,struct pci_dev*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sdv_gpio_probe(struct pci_dev *pdev,
					const struct pci_device_id *pci_id)
{
	struct sdv_gpio_chip_data *sd;
	unsigned long addr;
	const void *prop;
	int len;
	int ret;
	u32 mux_val;

	sd = kzalloc(sizeof(struct sdv_gpio_chip_data), GFP_KERNEL);
	if (!sd)
		return -ENOMEM;
	ret = pci_enable_device(pdev);
	if (ret) {
		dev_err(&pdev->dev, "can't enable device.\n");
		goto done;
	}

	ret = pci_request_region(pdev, GPIO_BAR, DRV_NAME);
	if (ret) {
		dev_err(&pdev->dev, "can't alloc PCI BAR #%d\n", GPIO_BAR);
		goto disable_pci;
	}

	addr = pci_resource_start(pdev, GPIO_BAR);
	if (!addr) {
		ret = -ENODEV;
		goto release_reg;
	}
	sd->gpio_pub_base = ioremap(addr, pci_resource_len(pdev, GPIO_BAR));

	prop = of_get_property(pdev->dev.of_node, "intel,muxctl", &len);
	if (prop && len == 4) {
		mux_val = of_read_number(prop, 1);
		writel(mux_val, sd->gpio_pub_base + GPMUXCTL);
	}

	ret = bgpio_init(&sd->chip, &pdev->dev, 4,
			sd->gpio_pub_base + GPINR, sd->gpio_pub_base + GPOUTR,
			NULL, sd->gpio_pub_base + GPOER, NULL, 0);
	if (ret)
		goto unmap;
	sd->chip.ngpio = SDV_NUM_PUB_GPIOS;

	ret = gpiochip_add_data(&sd->chip, sd);
	if (ret < 0) {
		dev_err(&pdev->dev, "gpiochip_add() failed.\n");
		goto unmap;
	}

	ret = sdv_register_irqsupport(sd, pdev);
	if (ret)
		goto unmap;

	pci_set_drvdata(pdev, sd);
	dev_info(&pdev->dev, "Sodaville GPIO driver registered.\n");
	return 0;

unmap:
	iounmap(sd->gpio_pub_base);
release_reg:
	pci_release_region(pdev, GPIO_BAR);
disable_pci:
	pci_disable_device(pdev);
done:
	kfree(sd);
	return ret;
}