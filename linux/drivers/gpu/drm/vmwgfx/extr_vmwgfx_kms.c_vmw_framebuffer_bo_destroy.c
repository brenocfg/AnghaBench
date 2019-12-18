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
struct vmw_framebuffer_bo {TYPE_1__ base; int /*<<< orphan*/  buffer; } ;
struct drm_framebuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_framebuffer_cleanup (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  kfree (struct vmw_framebuffer_bo*) ; 
 int /*<<< orphan*/  ttm_base_object_unref (scalar_t__*) ; 
 int /*<<< orphan*/  vmw_bo_unreference (int /*<<< orphan*/ *) ; 
 struct vmw_framebuffer_bo* vmw_framebuffer_to_vfbd (struct drm_framebuffer*) ; 

__attribute__((used)) static void vmw_framebuffer_bo_destroy(struct drm_framebuffer *framebuffer)
{
	struct vmw_framebuffer_bo *vfbd =
		vmw_framebuffer_to_vfbd(framebuffer);

	drm_framebuffer_cleanup(framebuffer);
	vmw_bo_unreference(&vfbd->buffer);
	if (vfbd->base.user_obj)
		ttm_base_object_unref(&vfbd->base.user_obj);

	kfree(vfbd);
}