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
struct TYPE_2__ {scalar_t__ platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct b53_device {scalar_t__ pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  b53_spi_ops ; 
 struct b53_device* b53_switch_alloc (TYPE_1__*,int /*<<< orphan*/ *,struct spi_device*) ; 
 int b53_switch_register (struct b53_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct b53_device*) ; 

__attribute__((used)) static int b53_spi_probe(struct spi_device *spi)
{
	struct b53_device *dev;
	int ret;

	dev = b53_switch_alloc(&spi->dev, &b53_spi_ops, spi);
	if (!dev)
		return -ENOMEM;

	if (spi->dev.platform_data)
		dev->pdata = spi->dev.platform_data;

	ret = b53_switch_register(dev);
	if (ret)
		return ret;

	spi_set_drvdata(spi, dev);

	return 0;
}