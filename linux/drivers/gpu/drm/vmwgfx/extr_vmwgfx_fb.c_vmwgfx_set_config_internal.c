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
struct drm_mode_set {struct drm_crtc* crtc; } ;
struct drm_crtc {TYPE_1__* funcs; } ;
struct TYPE_2__ {int (* set_config ) (struct drm_mode_set*,struct drm_modeset_acquire_ctx*) ;} ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  drm_modeset_acquire_fini (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_acquire_init (struct drm_modeset_acquire_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_modeset_backoff (struct drm_modeset_acquire_ctx*) ; 
 int /*<<< orphan*/  drm_modeset_drop_locks (struct drm_modeset_acquire_ctx*) ; 
 int stub1 (struct drm_mode_set*,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static int vmwgfx_set_config_internal(struct drm_mode_set *set)
{
	struct drm_crtc *crtc = set->crtc;
	struct drm_modeset_acquire_ctx ctx;
	int ret;

	drm_modeset_acquire_init(&ctx, 0);

restart:
	ret = crtc->funcs->set_config(set, &ctx);

	if (ret == -EDEADLK) {
		drm_modeset_backoff(&ctx);
		goto restart;
	}

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	return ret;
}