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
struct tegra_dc {int /*<<< orphan*/  syncpt; int /*<<< orphan*/  group; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq; } ;
struct host1x_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_dc*) ; 
 int /*<<< orphan*/  host1x_client_iommu_detach (struct host1x_client*,int /*<<< orphan*/ ) ; 
 struct tegra_dc* host1x_client_to_dc (struct host1x_client*) ; 
 int /*<<< orphan*/  host1x_syncpt_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_has_window_groups (struct tegra_dc*) ; 
 int tegra_dc_rgb_exit (struct tegra_dc*) ; 

__attribute__((used)) static int tegra_dc_exit(struct host1x_client *client)
{
	struct tegra_dc *dc = host1x_client_to_dc(client);
	int err;

	if (!tegra_dc_has_window_groups(dc))
		return 0;

	devm_free_irq(dc->dev, dc->irq, dc);

	err = tegra_dc_rgb_exit(dc);
	if (err) {
		dev_err(dc->dev, "failed to shutdown RGB output: %d\n", err);
		return err;
	}

	host1x_client_iommu_detach(client, dc->group);
	host1x_syncpt_free(dc->syncpt);

	return 0;
}