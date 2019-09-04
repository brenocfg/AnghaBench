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
struct TYPE_2__ {scalar_t__ user_obj; } ;
struct vmw_framebuffer_surface {TYPE_1__ base; int /*<<< orphan*/  surface; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  kfree (struct vmw_framebuffer_surface*) ; 
 int /*<<< orphan*/  ttm_base_object_unref (scalar_t__*) ; 
 struct vmw_framebuffer_surface* vmw_framebuffer_to_vfbs (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  vmw_surface_unreference (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vmw_framebuffer_surface_destroy(struct drm_framebuffer *framebuffer)
{
	struct vmw_framebuffer_surface *vfbs =
		vmw_framebuffer_to_vfbs(framebuffer);

	drm_framebuffer_cleanup(framebuffer);
	vmw_surface_unreference(&vfbs->surface);
	if (vfbs->base.user_obj)
		ttm_base_object_unref(&vfbs->base.user_obj);

	kfree(vfbs);
}