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
struct drm_ctx {scalar_t__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_KMS_LEGACY_CONTEXT ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 

int drm_legacy_getctx(struct drm_device *dev, void *data,
		      struct drm_file *file_priv)
{
	struct drm_ctx *ctx = data;

	if (!drm_core_check_feature(dev, DRIVER_KMS_LEGACY_CONTEXT) &&
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		return -EOPNOTSUPP;

	/* This is 0, because we don't handle any context flags */
	ctx->flags = 0;

	return 0;
}