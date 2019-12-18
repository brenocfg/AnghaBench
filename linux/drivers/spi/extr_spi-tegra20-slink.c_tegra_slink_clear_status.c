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
typedef  int u32 ;
struct tegra_slink_data {int dummy; } ;

/* Variables and functions */
 int SLINK_FIFO_ERROR ; 
 int SLINK_RDY ; 
 int /*<<< orphan*/  SLINK_STATUS ; 
 int /*<<< orphan*/  tegra_slink_readl (struct tegra_slink_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_slink_writel (struct tegra_slink_data*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_slink_clear_status(struct tegra_slink_data *tspi)
{
	u32 val_write;

	tegra_slink_readl(tspi, SLINK_STATUS);

	/* Write 1 to clear status register */
	val_write = SLINK_RDY | SLINK_FIFO_ERROR;
	tegra_slink_writel(tspi, val_write, SLINK_STATUS);
}