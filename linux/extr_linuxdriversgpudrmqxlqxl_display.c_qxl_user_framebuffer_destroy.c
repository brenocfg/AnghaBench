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
struct qxl_framebuffer {int /*<<< orphan*/  obj; } ;
struct qxl_bo {int /*<<< orphan*/  shadow; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_gem_object_put_unlocked (int /*<<< orphan*/ ) ; 
 struct qxl_bo* gem_to_qxl_bo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qxl_framebuffer*) ; 
 struct qxl_framebuffer* to_qxl_framebuffer (struct drm_framebuffer*) ; 

void qxl_user_framebuffer_destroy(struct drm_framebuffer *fb)
{
	struct qxl_framebuffer *qxl_fb = to_qxl_framebuffer(fb);
	struct qxl_bo *bo = gem_to_qxl_bo(qxl_fb->obj);

	WARN_ON(bo->shadow);
	drm_gem_object_put_unlocked(qxl_fb->obj);
	drm_framebuffer_cleanup(fb);
	kfree(qxl_fb);
}