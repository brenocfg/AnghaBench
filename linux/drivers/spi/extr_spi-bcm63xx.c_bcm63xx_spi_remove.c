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
struct platform_device {int dummy; } ;
struct bcm63xx_spi {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_INT_MASK ; 
 int /*<<< orphan*/  bcm_spi_writeb (struct bcm63xx_spi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 struct bcm63xx_spi* spi_master_get_devdata (struct spi_master*) ; 

__attribute__((used)) static int bcm63xx_spi_remove(struct platform_device *pdev)
{
	struct spi_master *master = platform_get_drvdata(pdev);
	struct bcm63xx_spi *bs = spi_master_get_devdata(master);

	/* reset spi block */
	bcm_spi_writeb(bs, 0, SPI_INT_MASK);

	/* HW shutdown */
	clk_disable_unprepare(bs->clk);

	return 0;
}