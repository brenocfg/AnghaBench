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
struct ksz_device {scalar_t__ pdata; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ksz_spi_ops ; 
 struct ksz_device* ksz_switch_alloc (TYPE_1__*,int /*<<< orphan*/ *,struct spi_device*) ; 
 int ksz_switch_register (struct ksz_device*) ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct ksz_device*) ; 

__attribute__((used)) static int ksz_spi_probe(struct spi_device *spi)
{
	struct ksz_device *dev;
	int ret;

	dev = ksz_switch_alloc(&spi->dev, &ksz_spi_ops, spi);
	if (!dev)
		return -ENOMEM;

	if (spi->dev.platform_data)
		dev->pdata = spi->dev.platform_data;

	ret = ksz_switch_register(dev);
	if (ret)
		return ret;

	spi_set_drvdata(spi, dev);

	return 0;
}