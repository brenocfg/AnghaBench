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
struct tegra_sflash_data {int dummy; } ;

/* Variables and functions */
 int SPI_FIFO_ERROR ; 
 int SPI_RDY ; 
 int /*<<< orphan*/  SPI_STATUS ; 
 int /*<<< orphan*/  tegra_sflash_writel (struct tegra_sflash_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_sflash_clear_status(struct tegra_sflash_data *tsd)
{
	/* Write 1 to clear status register */
	tegra_sflash_writel(tsd, SPI_RDY | SPI_FIFO_ERROR, SPI_STATUS);
}