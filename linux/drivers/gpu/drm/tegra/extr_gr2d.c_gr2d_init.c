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
struct host1x_client {int /*<<< orphan*/ * syncpts; int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct gr2d {int /*<<< orphan*/  channel; int /*<<< orphan*/  group; } ;
struct drm_device {int /*<<< orphan*/  dev_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned long HOST1X_SYNCPT_HAS_BASE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_channel_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_channel_request (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_client_iommu_attach (struct host1x_client*,int) ; 
 int /*<<< orphan*/  host1x_client_iommu_detach (struct host1x_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_request (struct host1x_client*,unsigned long) ; 
 struct tegra_drm_client* host1x_to_drm_client (struct host1x_client*) ; 
 int tegra_drm_register_client (int /*<<< orphan*/ ,struct tegra_drm_client*) ; 
 struct gr2d* to_gr2d (struct tegra_drm_client*) ; 

__attribute__((used)) static int gr2d_init(struct host1x_client *client)
{
	struct tegra_drm_client *drm = host1x_to_drm_client(client);
	struct drm_device *dev = dev_get_drvdata(client->parent);
	unsigned long flags = HOST1X_SYNCPT_HAS_BASE;
	struct gr2d *gr2d = to_gr2d(drm);
	int err;

	gr2d->channel = host1x_channel_request(client->dev);
	if (!gr2d->channel)
		return -ENOMEM;

	client->syncpts[0] = host1x_syncpt_request(client, flags);
	if (!client->syncpts[0]) {
		err = -ENOMEM;
		dev_err(client->dev, "failed to request syncpoint: %d\n", err);
		goto put;
	}

	gr2d->group = host1x_client_iommu_attach(client, false);
	if (IS_ERR(gr2d->group)) {
		err = PTR_ERR(gr2d->group);
		dev_err(client->dev, "failed to attach to domain: %d\n", err);
		goto free;
	}

	err = tegra_drm_register_client(dev->dev_private, drm);
	if (err < 0) {
		dev_err(client->dev, "failed to register client: %d\n", err);
		goto detach;
	}

	return 0;

detach:
	host1x_client_iommu_detach(client, gr2d->group);
free:
	host1x_syncpt_free(client->syncpts[0]);
put:
	host1x_channel_put(gr2d->channel);
	return err;
}