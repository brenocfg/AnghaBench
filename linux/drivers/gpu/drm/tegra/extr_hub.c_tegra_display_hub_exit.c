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
struct tegra_drm {TYPE_1__* hub; } ;
struct host1x_client {int /*<<< orphan*/  parent; } ;
struct drm_device {struct tegra_drm* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_private_obj_fini (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_display_hub_exit(struct host1x_client *client)
{
	struct drm_device *drm = dev_get_drvdata(client->parent);
	struct tegra_drm *tegra = drm->dev_private;

	drm_atomic_private_obj_fini(&tegra->hub->base);
	tegra->hub = NULL;

	return 0;
}