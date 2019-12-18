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
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_ctx {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_KMS_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_context_switch_complete (struct drm_device*,struct drm_file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 

int drm_legacy_newctx(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct drm_ctx *ctx = data;

	if (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		return -EOPNOTSUPP;

	DRM_DEBUG("%d\n", ctx->handle);
	drm_context_switch_complete(dev, file_priv, ctx->handle);

	return 0;
}