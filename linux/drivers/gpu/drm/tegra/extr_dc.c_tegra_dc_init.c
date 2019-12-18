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
struct tegra_drm {scalar_t__ pitch_align; } ;
struct tegra_dc {int /*<<< orphan*/  syncpt; struct drm_plane* group; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_1__* soc; int /*<<< orphan*/  base; } ;
struct host1x_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  parent; } ;
struct drm_plane {int dummy; } ;
struct drm_device {struct tegra_drm* dev_private; } ;
struct TYPE_2__ {scalar_t__ pitch_align; scalar_t__ supports_cursor; scalar_t__ wgrps; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned long HOST1X_SYNCPT_CLIENT_MANAGED ; 
 scalar_t__ IS_ERR (struct drm_plane*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct drm_plane*) ; 
 int PTR_ERR (struct drm_plane*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 struct drm_device* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tegra_dc*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,struct drm_plane*,struct drm_plane*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 struct drm_plane* host1x_client_iommu_attach (struct host1x_client*,int) ; 
 int /*<<< orphan*/  host1x_client_iommu_detach (struct host1x_client*,struct drm_plane*) ; 
 struct tegra_dc* host1x_client_to_dc (struct host1x_client*) ; 
 int /*<<< orphan*/  host1x_syncpt_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_syncpt_request (struct host1x_client*,unsigned long) ; 
 int /*<<< orphan*/  tegra_crtc_funcs ; 
 int /*<<< orphan*/  tegra_crtc_helper_funcs ; 
 struct drm_plane* tegra_dc_add_planes (struct drm_device*,struct tegra_dc*) ; 
 struct drm_plane* tegra_dc_add_shared_planes (struct drm_device*,struct tegra_dc*) ; 
 struct drm_plane* tegra_dc_cursor_plane_create (struct drm_device*,struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_has_window_groups (struct tegra_dc*) ; 
 int /*<<< orphan*/  tegra_dc_irq ; 
 struct drm_plane* tegra_dc_overlay_plane_create (struct drm_device*,struct tegra_dc*,int,int) ; 
 int tegra_dc_rgb_init (struct drm_device*,struct tegra_dc*) ; 

__attribute__((used)) static int tegra_dc_init(struct host1x_client *client)
{
	struct drm_device *drm = dev_get_drvdata(client->parent);
	unsigned long flags = HOST1X_SYNCPT_CLIENT_MANAGED;
	struct tegra_dc *dc = host1x_client_to_dc(client);
	struct tegra_drm *tegra = drm->dev_private;
	struct drm_plane *primary = NULL;
	struct drm_plane *cursor = NULL;
	int err;

	/*
	 * XXX do not register DCs with no window groups because we cannot
	 * assign a primary plane to them, which in turn will cause KMS to
	 * crash.
	 */
	if (!tegra_dc_has_window_groups(dc))
		return 0;

	dc->syncpt = host1x_syncpt_request(client, flags);
	if (!dc->syncpt)
		dev_warn(dc->dev, "failed to allocate syncpoint\n");

	dc->group = host1x_client_iommu_attach(client, true);
	if (IS_ERR(dc->group)) {
		err = PTR_ERR(dc->group);
		dev_err(client->dev, "failed to attach to domain: %d\n", err);
		return err;
	}

	if (dc->soc->wgrps)
		primary = tegra_dc_add_shared_planes(drm, dc);
	else
		primary = tegra_dc_add_planes(drm, dc);

	if (IS_ERR(primary)) {
		err = PTR_ERR(primary);
		goto cleanup;
	}

	if (dc->soc->supports_cursor) {
		cursor = tegra_dc_cursor_plane_create(drm, dc);
		if (IS_ERR(cursor)) {
			err = PTR_ERR(cursor);
			goto cleanup;
		}
	} else {
		/* dedicate one overlay to mouse cursor */
		cursor = tegra_dc_overlay_plane_create(drm, dc, 2, true);
		if (IS_ERR(cursor)) {
			err = PTR_ERR(cursor);
			goto cleanup;
		}
	}

	err = drm_crtc_init_with_planes(drm, &dc->base, primary, cursor,
					&tegra_crtc_funcs, NULL);
	if (err < 0)
		goto cleanup;

	drm_crtc_helper_add(&dc->base, &tegra_crtc_helper_funcs);

	/*
	 * Keep track of the minimum pitch alignment across all display
	 * controllers.
	 */
	if (dc->soc->pitch_align > tegra->pitch_align)
		tegra->pitch_align = dc->soc->pitch_align;

	err = tegra_dc_rgb_init(drm, dc);
	if (err < 0 && err != -ENODEV) {
		dev_err(dc->dev, "failed to initialize RGB output: %d\n", err);
		goto cleanup;
	}

	err = devm_request_irq(dc->dev, dc->irq, tegra_dc_irq, 0,
			       dev_name(dc->dev), dc);
	if (err < 0) {
		dev_err(dc->dev, "failed to request IRQ#%u: %d\n", dc->irq,
			err);
		goto cleanup;
	}

	return 0;

cleanup:
	if (!IS_ERR_OR_NULL(cursor))
		drm_plane_cleanup(cursor);

	if (!IS_ERR(primary))
		drm_plane_cleanup(primary);

	host1x_client_iommu_detach(client, dc->group);
	host1x_syncpt_free(dc->syncpt);

	return err;
}