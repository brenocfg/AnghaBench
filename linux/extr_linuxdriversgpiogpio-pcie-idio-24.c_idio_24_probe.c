#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct device {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  irq; struct device dev; } ;
struct TYPE_5__ {char* label; int base; int /*<<< orphan*/  set_multiple; int /*<<< orphan*/  set; int /*<<< orphan*/  get_multiple; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get_direction; int /*<<< orphan*/  names; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  owner; struct device* parent; } ;
struct idio_24_gpio {TYPE_2__ chip; TYPE_1__* reg; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  soft_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (size_t const) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDIO_24_NGPIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device* const,char*,int) ; 
 int devm_gpiochip_add_data (struct device* const,TYPE_2__*,struct idio_24_gpio*) ; 
 struct idio_24_gpio* devm_kzalloc (struct device* const,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,struct idio_24_gpio*) ; 
 int gpiochip_irqchip_add (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_edge_irq ; 
 int /*<<< orphan*/  idio_24_gpio_direction_input ; 
 int /*<<< orphan*/  idio_24_gpio_direction_output ; 
 int /*<<< orphan*/  idio_24_gpio_get ; 
 int /*<<< orphan*/  idio_24_gpio_get_direction ; 
 int /*<<< orphan*/  idio_24_gpio_get_multiple ; 
 int /*<<< orphan*/  idio_24_gpio_set ; 
 int /*<<< orphan*/  idio_24_gpio_set_multiple ; 
 int /*<<< orphan*/  idio_24_irq_handler ; 
 int /*<<< orphan*/  idio_24_irqchip ; 
 int /*<<< orphan*/  idio_24_names ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* pci_name (struct pci_dev*) ; 
 int pcim_enable_device (struct pci_dev*) ; 
 int pcim_iomap_regions (struct pci_dev*,int /*<<< orphan*/ ,char const* const) ; 
 TYPE_1__** pcim_iomap_table (struct pci_dev*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idio_24_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct device *const dev = &pdev->dev;
	struct idio_24_gpio *idio24gpio;
	int err;
	const size_t pci_bar_index = 2;
	const char *const name = pci_name(pdev);

	idio24gpio = devm_kzalloc(dev, sizeof(*idio24gpio), GFP_KERNEL);
	if (!idio24gpio)
		return -ENOMEM;

	err = pcim_enable_device(pdev);
	if (err) {
		dev_err(dev, "Failed to enable PCI device (%d)\n", err);
		return err;
	}

	err = pcim_iomap_regions(pdev, BIT(pci_bar_index), name);
	if (err) {
		dev_err(dev, "Unable to map PCI I/O addresses (%d)\n", err);
		return err;
	}

	idio24gpio->reg = pcim_iomap_table(pdev)[pci_bar_index];

	idio24gpio->chip.label = name;
	idio24gpio->chip.parent = dev;
	idio24gpio->chip.owner = THIS_MODULE;
	idio24gpio->chip.base = -1;
	idio24gpio->chip.ngpio = IDIO_24_NGPIO;
	idio24gpio->chip.names = idio_24_names;
	idio24gpio->chip.get_direction = idio_24_gpio_get_direction;
	idio24gpio->chip.direction_input = idio_24_gpio_direction_input;
	idio24gpio->chip.direction_output = idio_24_gpio_direction_output;
	idio24gpio->chip.get = idio_24_gpio_get;
	idio24gpio->chip.get_multiple = idio_24_gpio_get_multiple;
	idio24gpio->chip.set = idio_24_gpio_set;
	idio24gpio->chip.set_multiple = idio_24_gpio_set_multiple;

	raw_spin_lock_init(&idio24gpio->lock);

	/* Software board reset */
	iowrite8(0, &idio24gpio->reg->soft_reset);

	err = devm_gpiochip_add_data(dev, &idio24gpio->chip, idio24gpio);
	if (err) {
		dev_err(dev, "GPIO registering failed (%d)\n", err);
		return err;
	}

	err = gpiochip_irqchip_add(&idio24gpio->chip, &idio_24_irqchip, 0,
		handle_edge_irq, IRQ_TYPE_NONE);
	if (err) {
		dev_err(dev, "Could not add irqchip (%d)\n", err);
		return err;
	}

	err = devm_request_irq(dev, pdev->irq, idio_24_irq_handler, IRQF_SHARED,
		name, idio24gpio);
	if (err) {
		dev_err(dev, "IRQ handler registering failed (%d)\n", err);
		return err;
	}

	return 0;
}