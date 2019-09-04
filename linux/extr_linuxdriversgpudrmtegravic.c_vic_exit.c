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
struct vic {int /*<<< orphan*/ * domain; int /*<<< orphan*/  channel; } ;
struct tegra_drm_client {int dummy; } ;
struct tegra_drm {int dummy; } ;
struct iommu_group {int dummy; } ;
struct host1x_client {int /*<<< orphan*/ * syncpts; int /*<<< orphan*/  parent; int /*<<< orphan*/  dev; } ;
struct drm_device {struct tegra_drm* dev_private; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_channel_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_free (int /*<<< orphan*/ ) ; 
 struct tegra_drm_client* host1x_to_drm_client (struct host1x_client*) ; 
 int /*<<< orphan*/  iommu_detach_group (int /*<<< orphan*/ *,struct iommu_group*) ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ ) ; 
 int tegra_drm_unregister_client (struct tegra_drm*,struct tegra_drm_client*) ; 
 struct vic* to_vic (struct tegra_drm_client*) ; 

__attribute__((used)) static int vic_exit(struct host1x_client *client)
{
	struct tegra_drm_client *drm = host1x_to_drm_client(client);
	struct iommu_group *group = iommu_group_get(client->dev);
	struct drm_device *dev = dev_get_drvdata(client->parent);
	struct tegra_drm *tegra = dev->dev_private;
	struct vic *vic = to_vic(drm);
	int err;

	err = tegra_drm_unregister_client(tegra, drm);
	if (err < 0)
		return err;

	host1x_syncpt_free(client->syncpts[0]);
	host1x_channel_put(vic->channel);

	if (vic->domain) {
		iommu_detach_group(vic->domain, group);
		vic->domain = NULL;
	}

	return 0;
}