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
struct tegra_dc {int /*<<< orphan*/ * debugfs_files; } ;
struct drm_minor {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct drm_minor* primary; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_files ; 
 int /*<<< orphan*/  drm_debugfs_remove_files (int /*<<< orphan*/ *,unsigned int,struct drm_minor*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 struct tegra_dc* to_tegra_dc (struct drm_crtc*) ; 

__attribute__((used)) static void tegra_dc_early_unregister(struct drm_crtc *crtc)
{
	unsigned int count = ARRAY_SIZE(debugfs_files);
	struct drm_minor *minor = crtc->dev->primary;
	struct tegra_dc *dc = to_tegra_dc(crtc);

	drm_debugfs_remove_files(dc->debugfs_files, count, minor);
	kfree(dc->debugfs_files);
	dc->debugfs_files = NULL;
}