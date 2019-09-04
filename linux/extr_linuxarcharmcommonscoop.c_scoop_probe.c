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
struct TYPE_5__ {int base; int ngpio; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; int /*<<< orphan*/  get; int /*<<< orphan*/  set; int /*<<< orphan*/  label; } ;
struct scoop_dev {scalar_t__ base; TYPE_2__ gpio; int /*<<< orphan*/  suspend_set; int /*<<< orphan*/  suspend_clr; int /*<<< orphan*/  scoop_lock; } ;
struct scoop_config {int io_dir; int io_out; int gpio_base; int /*<<< orphan*/  suspend_set; int /*<<< orphan*/  suspend_clr; } ;
struct resource {scalar_t__ start; } ;
struct TYPE_4__ {struct scoop_config* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ SCOOP_CPR ; 
 scalar_t__ SCOOP_GPCR ; 
 scalar_t__ SCOOP_GPWR ; 
 scalar_t__ SCOOP_MCR ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int gpiochip_add_data (TYPE_2__*,struct scoop_dev*) ; 
 scalar_t__ ioremap (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iowrite16 (int,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct scoop_dev*) ; 
 struct scoop_dev* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct scoop_dev*) ; 
 int /*<<< orphan*/  printk (char*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  reset_scoop (TYPE_1__*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  scoop_gpio_direction_input ; 
 int /*<<< orphan*/  scoop_gpio_direction_output ; 
 int /*<<< orphan*/  scoop_gpio_get ; 
 int /*<<< orphan*/  scoop_gpio_set ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scoop_probe(struct platform_device *pdev)
{
	struct scoop_dev *devptr;
	struct scoop_config *inf;
	struct resource *mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	int ret;

	if (!mem)
		return -EINVAL;

	devptr = kzalloc(sizeof(struct scoop_dev), GFP_KERNEL);
	if (!devptr)
		return -ENOMEM;

	spin_lock_init(&devptr->scoop_lock);

	inf = pdev->dev.platform_data;
	devptr->base = ioremap(mem->start, resource_size(mem));

	if (!devptr->base) {
		ret = -ENOMEM;
		goto err_ioremap;
	}

	platform_set_drvdata(pdev, devptr);

	printk("Sharp Scoop Device found at 0x%08x -> 0x%8p\n",(unsigned int)mem->start, devptr->base);

	iowrite16(0x0140, devptr->base + SCOOP_MCR);
	reset_scoop(&pdev->dev);
	iowrite16(0x0000, devptr->base + SCOOP_CPR);
	iowrite16(inf->io_dir & 0xffff, devptr->base + SCOOP_GPCR);
	iowrite16(inf->io_out & 0xffff, devptr->base + SCOOP_GPWR);

	devptr->suspend_clr = inf->suspend_clr;
	devptr->suspend_set = inf->suspend_set;

	devptr->gpio.base = -1;

	if (inf->gpio_base != 0) {
		devptr->gpio.label = dev_name(&pdev->dev);
		devptr->gpio.base = inf->gpio_base;
		devptr->gpio.ngpio = 12; /* PA11 = 0, PA12 = 1, etc. up to PA22 = 11 */
		devptr->gpio.set = scoop_gpio_set;
		devptr->gpio.get = scoop_gpio_get;
		devptr->gpio.direction_input = scoop_gpio_direction_input;
		devptr->gpio.direction_output = scoop_gpio_direction_output;

		ret = gpiochip_add_data(&devptr->gpio, devptr);
		if (ret)
			goto err_gpio;
	}

	return 0;

err_gpio:
	platform_set_drvdata(pdev, NULL);
err_ioremap:
	iounmap(devptr->base);
	kfree(devptr);

	return ret;
}