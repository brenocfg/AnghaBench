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
struct dataflash {int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (struct dataflash*) ; 
 int mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct dataflash* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int dataflash_remove(struct spi_device *spi)
{
	struct dataflash	*flash = spi_get_drvdata(spi);
	int			status;

	dev_dbg(&spi->dev, "remove\n");

	status = mtd_device_unregister(&flash->mtd);
	if (status == 0)
		kfree(flash);
	return status;
}