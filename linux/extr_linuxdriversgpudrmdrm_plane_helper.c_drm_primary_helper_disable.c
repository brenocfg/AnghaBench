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
struct drm_plane {int dummy; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

int drm_primary_helper_disable(struct drm_plane *plane,
			       struct drm_modeset_acquire_ctx *ctx)
{
	return -EINVAL;
}