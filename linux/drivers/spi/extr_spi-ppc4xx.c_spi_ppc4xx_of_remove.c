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
struct ppc4xx_spi {int /*<<< orphan*/  regs; int /*<<< orphan*/  irqnum; int /*<<< orphan*/  mapsize; int /*<<< orphan*/  mapbase; int /*<<< orphan*/  bitbang; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_gpios (struct ppc4xx_spi*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ppc4xx_spi*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 struct spi_master* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_bitbang_stop (int /*<<< orphan*/ *) ; 
 struct ppc4xx_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  spi_master_put (struct spi_master*) ; 

__attribute__((used)) static int spi_ppc4xx_of_remove(struct platform_device *op)
{
	struct spi_master *master = platform_get_drvdata(op);
	struct ppc4xx_spi *hw = spi_master_get_devdata(master);

	spi_bitbang_stop(&hw->bitbang);
	release_mem_region(hw->mapbase, hw->mapsize);
	free_irq(hw->irqnum, hw);
	iounmap(hw->regs);
	free_gpios(hw);
	spi_master_put(master);
	return 0;
}