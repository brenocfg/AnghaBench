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
struct spi_device {int dummy; } ;
struct mchp23k256_flash {int /*<<< orphan*/  mtd; } ;

/* Variables and functions */
 int mtd_device_unregister (int /*<<< orphan*/ *) ; 
 struct mchp23k256_flash* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int mchp23k256_remove(struct spi_device *spi)
{
	struct mchp23k256_flash *flash = spi_get_drvdata(spi);

	return mtd_device_unregister(&flash->mtd);
}