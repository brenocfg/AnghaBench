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
struct spi_master {int dummy; } ;
struct sifive_spi {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFIVE_SPI_REG_IE ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sifive_spi_write (struct sifive_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sifive_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int sifive_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct sifive_spi *spi = spi_master_get_devdata(master);

	/* Disable all the interrupts just in case */
	sifive_spi_write(spi, SIFIVE_SPI_REG_IE, 0);

	return 0;
}