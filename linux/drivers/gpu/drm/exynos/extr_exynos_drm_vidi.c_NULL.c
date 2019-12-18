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
struct vidi_context {int connected; int /*<<< orphan*/  drm_dev; struct edid* raw_edid; int /*<<< orphan*/  dev; } ;
struct edid {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_exynos_vidi_connection {int connection; scalar_t__ edid; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct vidi_context* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct edid* drm_edid_duplicate (struct edid*) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 int /*<<< orphan*/  drm_helper_hpd_irq_event (int /*<<< orphan*/ ) ; 
 scalar_t__ fake_edid_info ; 
 int /*<<< orphan*/  kfree (struct edid*) ; 

int vidi_connection_ioctl(struct drm_device *drm_dev, void *data,
				struct drm_file *file_priv)
{
	struct vidi_context *ctx = dev_get_drvdata(drm_dev->dev);
	struct drm_exynos_vidi_connection *vidi = data;

	if (!vidi) {
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "user data for vidi is null.\n");
		return -EINVAL;
	}

	if (vidi->connection > 1) {
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "connection should be 0 or 1.\n");
		return -EINVAL;
	}

	if (ctx->connected == vidi->connection) {
		DRM_DEV_DEBUG_KMS(ctx->dev,
				  "same connection request.\n");
		return -EINVAL;
	}

	if (vidi->connection) {
		struct edid *raw_edid;

		raw_edid = (struct edid *)(unsigned long)vidi->edid;
		if (!drm_edid_is_valid(raw_edid)) {
			DRM_DEV_DEBUG_KMS(ctx->dev,
					  "edid data is invalid.\n");
			return -EINVAL;
		}
		ctx->raw_edid = drm_edid_duplicate(raw_edid);
		if (!ctx->raw_edid) {
			DRM_DEV_DEBUG_KMS(ctx->dev,
					  "failed to allocate raw_edid.\n");
			return -ENOMEM;
		}
	} else {
		/*
		 * with connection = 0, free raw_edid
		 * only if raw edid data isn't same as fake data.
		 */
		if (ctx->raw_edid && ctx->raw_edid !=
				(struct edid *)fake_edid_info) {
			kfree(ctx->raw_edid);
			ctx->raw_edid = NULL;
		}
	}

	ctx->connected = vidi->connection;
	drm_helper_hpd_irq_event(ctx->drm_dev);

	return 0;
}