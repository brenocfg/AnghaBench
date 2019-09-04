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
typedef  int u32 ;
struct drm_file {int /*<<< orphan*/  authenticated; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int DRM_AUTH ; 
 int DRM_MASTER ; 
 int DRM_RENDER_ALLOW ; 
 int DRM_ROOT_ONLY ; 
 int EACCES ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_is_current_master (struct drm_file*) ; 
 scalar_t__ drm_is_render_client (struct drm_file*) ; 
 scalar_t__ unlikely (int) ; 

int drm_ioctl_permit(u32 flags, struct drm_file *file_priv)
{
	/* ROOT_ONLY is only for CAP_SYS_ADMIN */
	if (unlikely((flags & DRM_ROOT_ONLY) && !capable(CAP_SYS_ADMIN)))
		return -EACCES;

	/* AUTH is only for authenticated or render client */
	if (unlikely((flags & DRM_AUTH) && !drm_is_render_client(file_priv) &&
		     !file_priv->authenticated))
		return -EACCES;

	/* MASTER is only for master or control clients */
	if (unlikely((flags & DRM_MASTER) &&
		     !drm_is_current_master(file_priv)))
		return -EACCES;

	/* Render clients must be explicitly allowed */
	if (unlikely(!(flags & DRM_RENDER_ALLOW) &&
		     drm_is_render_client(file_priv)))
		return -EACCES;

	return 0;
}