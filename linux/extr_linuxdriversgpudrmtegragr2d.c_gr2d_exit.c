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
struct tegra_drm_client {int dummy; } ;
struct tegra_drm {int dummy; } ;
struct host1x_client {int /*<<< orphan*/ * syncpts; int /*<<< orphan*/  parent; } ;
struct gr2d {int /*<<< orphan*/  channel; int /*<<< orphan*/  group; } ;
struct drm_device {struct tegra_drm* dev_private; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_channel_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_client_iommu_detach (struct host1x_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_free (int /*<<< orphan*/ ) ; 
 struct tegra_drm_client* host1x_to_drm_client (struct host1x_client*) ; 
 int tegra_drm_unregister_client (struct tegra_drm*,struct tegra_drm_client*) ; 
 struct gr2d* to_gr2d (struct tegra_drm_client*) ; 

__attribute__((used)) static int gr2d_exit(struct host1x_client *client)
{
	struct tegra_drm_client *drm = host1x_to_drm_client(client);
	struct drm_device *dev = dev_get_drvdata(client->parent);
	struct tegra_drm *tegra = dev->dev_private;
	struct gr2d *gr2d = to_gr2d(drm);
	int err;

	err = tegra_drm_unregister_client(tegra, drm);
	if (err < 0)
		return err;

	host1x_client_iommu_detach(client, gr2d->group);
	host1x_syncpt_free(client->syncpts[0]);
	host1x_channel_put(gr2d->channel);

	return 0;
}