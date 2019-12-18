#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tegra_output {int dummy; } ;
struct tegra_dsi {int /*<<< orphan*/ * debugfs_files; } ;
struct drm_connector {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct tegra_output* connector_to_output (struct drm_connector*) ; 
 int /*<<< orphan*/  debugfs_files ; 
 int /*<<< orphan*/  drm_debugfs_remove_files (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct tegra_dsi* to_dsi (struct tegra_output*) ; 

__attribute__((used)) static void tegra_dsi_early_unregister(struct drm_connector *connector)
{
	struct tegra_output *output = connector_to_output(connector);
	unsigned int count = ARRAY_SIZE(debugfs_files);
	struct tegra_dsi *dsi = to_dsi(output);

	drm_debugfs_remove_files(dsi->debugfs_files, count,
				 connector->dev->primary);
	kfree(dsi->debugfs_files);
	dsi->debugfs_files = NULL;
}