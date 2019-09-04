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
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_mode_set {TYPE_1__* mode; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int drm_atomic_helper_set_config (struct drm_mode_set*,struct drm_modeset_acquire_ctx*) ; 

int vmw_kms_set_config(struct drm_mode_set *set,
		       struct drm_modeset_acquire_ctx *ctx)
{
	if (set && set->mode)
		set->mode->type = 0;

	return drm_atomic_helper_set_config(set, ctx);
}