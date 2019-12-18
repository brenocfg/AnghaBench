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
struct vidi_context {int /*<<< orphan*/  dev; TYPE_1__* raw_edid; } ;
struct edid {int dummy; } ;
struct drm_connector {int dummy; } ;
struct TYPE_2__ {int extensions; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*) ; 
 int EDID_LENGTH ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct vidi_context* ctx_from_connector (struct drm_connector*) ; 
 int drm_add_edid_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  drm_connector_update_edid_property (struct drm_connector*,struct edid*) ; 
 struct edid* kmemdup (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidi_get_modes(struct drm_connector *connector)
{
	struct vidi_context *ctx = ctx_from_connector(connector);
	struct edid *edid;
	int edid_len;

	/*
	 * the edid data comes from user side and it would be set
	 * to ctx->raw_edid through specific ioctl.
	 */
	if (!ctx->raw_edid) {
		DRM_DEV_DEBUG_KMS(ctx->dev, "raw_edid is null.\n");
		return -EFAULT;
	}

	edid_len = (1 + ctx->raw_edid->extensions) * EDID_LENGTH;
	edid = kmemdup(ctx->raw_edid, edid_len, GFP_KERNEL);
	if (!edid) {
		DRM_DEV_DEBUG_KMS(ctx->dev, "failed to allocate edid\n");
		return -ENOMEM;
	}

	drm_connector_update_edid_property(connector, edid);

	return drm_add_edid_modes(connector, edid);
}