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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct dummy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_looptest ; 
 struct dummy* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dummy*) ; 

__attribute__((used)) static int pl022_dummy_remove(struct spi_device *spi)
{
	struct dummy *p_dummy = dev_get_drvdata(&spi->dev);

	dev_info(&spi->dev, "removing dummy SPI device\n");
	device_remove_file(&spi->dev, &dev_attr_looptest);
	dev_set_drvdata(&spi->dev, NULL);
	kfree(p_dummy);

	return 0;
}