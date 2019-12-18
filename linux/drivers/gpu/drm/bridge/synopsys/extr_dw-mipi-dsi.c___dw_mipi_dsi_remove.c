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
struct dw_mipi_dsi {int /*<<< orphan*/  dev; int /*<<< orphan*/  dsi_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_mipi_dsi_debugfs_remove (struct dw_mipi_dsi*) ; 
 int /*<<< orphan*/  mipi_dsi_host_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dw_mipi_dsi_remove(struct dw_mipi_dsi *dsi)
{
	mipi_dsi_host_unregister(&dsi->dsi_host);

	pm_runtime_disable(dsi->dev);
	dw_mipi_dsi_debugfs_remove(dsi);
}