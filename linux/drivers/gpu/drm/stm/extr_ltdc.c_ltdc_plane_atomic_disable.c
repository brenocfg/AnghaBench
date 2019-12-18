#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ltdc_device {int /*<<< orphan*/  regs; } ;
struct drm_plane_state {TYPE_2__* crtc; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int index; TYPE_3__ base; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LAY_OFS ; 
 int LTDC_L1CR ; 
 int /*<<< orphan*/  LXCR_LEN ; 
 struct ltdc_device* plane_to_ltdc (struct drm_plane*) ; 
 int /*<<< orphan*/  reg_clear (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltdc_plane_atomic_disable(struct drm_plane *plane,
				      struct drm_plane_state *oldstate)
{
	struct ltdc_device *ldev = plane_to_ltdc(plane);
	u32 lofs = plane->index * LAY_OFS;

	/* disable layer */
	reg_clear(ldev->regs, LTDC_L1CR + lofs, LXCR_LEN);

	DRM_DEBUG_DRIVER("CRTC:%d plane:%d\n",
			 oldstate->crtc->base.id, plane->base.id);
}