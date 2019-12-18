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
struct spi_driver {int (* probe ) (struct spi_device*) ;} ;
struct spi_device {int irq; } ;
struct device {scalar_t__ of_node; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int dev_pm_domain_attach (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_domain_detach (struct device*,int) ; 
 int of_clk_set_defaults (scalar_t__,int) ; 
 int of_irq_get (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (struct spi_device*) ; 
 struct spi_device* to_spi_device (struct device*) ; 
 struct spi_driver* to_spi_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spi_drv_probe(struct device *dev)
{
	const struct spi_driver		*sdrv = to_spi_driver(dev->driver);
	struct spi_device		*spi = to_spi_device(dev);
	int ret;

	ret = of_clk_set_defaults(dev->of_node, false);
	if (ret)
		return ret;

	if (dev->of_node) {
		spi->irq = of_irq_get(dev->of_node, 0);
		if (spi->irq == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		if (spi->irq < 0)
			spi->irq = 0;
	}

	ret = dev_pm_domain_attach(dev, true);
	if (ret)
		return ret;

	ret = sdrv->probe(spi);
	if (ret)
		dev_pm_domain_detach(dev, true);

	return ret;
}