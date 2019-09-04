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
struct resource {int /*<<< orphan*/  start; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct kempld_platform_data {int /*<<< orphan*/  pld_clock; } ;
struct kempld_device_data {int /*<<< orphan*/  lock; struct device* dev; int /*<<< orphan*/  pld_clock; scalar_t__ io_base; scalar_t__ io_data; scalar_t__ io_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 struct kempld_platform_data* dev_get_platdata (struct device*) ; 
 scalar_t__ devm_ioport_map (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kempld_device_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int kempld_detect_device (struct kempld_device_data*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct kempld_device_data*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int kempld_probe(struct platform_device *pdev)
{
	const struct kempld_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct device *dev = &pdev->dev;
	struct kempld_device_data *pld;
	struct resource *ioport;

	pld = devm_kzalloc(dev, sizeof(*pld), GFP_KERNEL);
	if (!pld)
		return -ENOMEM;

	ioport = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (!ioport)
		return -EINVAL;

	pld->io_base = devm_ioport_map(dev, ioport->start,
					resource_size(ioport));
	if (!pld->io_base)
		return -ENOMEM;

	pld->io_index = pld->io_base;
	pld->io_data = pld->io_base + 1;
	pld->pld_clock = pdata->pld_clock;
	pld->dev = dev;

	mutex_init(&pld->lock);
	platform_set_drvdata(pdev, pld);

	return kempld_detect_device(pld);
}