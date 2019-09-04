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
struct tegra_drm {struct iommu_group* group; scalar_t__ domain; } ;
struct iommu_group {int dummy; } ;
struct host1x_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct drm_device {struct tegra_drm* dev_private; } ;

/* Variables and functions */
 int ENODEV ; 
 struct iommu_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int iommu_attach_group (scalar_t__,struct iommu_group*) ; 
 struct iommu_group* iommu_group_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 

struct iommu_group *host1x_client_iommu_attach(struct host1x_client *client,
					       bool shared)
{
	struct drm_device *drm = dev_get_drvdata(client->parent);
	struct tegra_drm *tegra = drm->dev_private;
	struct iommu_group *group = NULL;
	int err;

	if (tegra->domain) {
		group = iommu_group_get(client->dev);
		if (!group) {
			dev_err(client->dev, "failed to get IOMMU group\n");
			return ERR_PTR(-ENODEV);
		}

		if (!shared || (shared && (group != tegra->group))) {
			err = iommu_attach_group(tegra->domain, group);
			if (err < 0) {
				iommu_group_put(group);
				return ERR_PTR(err);
			}

			if (shared && !tegra->group)
				tegra->group = group;
		}
	}

	return group;
}