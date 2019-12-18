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
struct mtk_ddp_comp {TYPE_1__* funcs; } ;
struct drm_crtc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* enable_vblank ) (struct mtk_ddp_comp*,struct drm_crtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mtk_ddp_comp*,struct drm_crtc*) ; 

__attribute__((used)) static inline void mtk_ddp_comp_enable_vblank(struct mtk_ddp_comp *comp,
					      struct drm_crtc *crtc)
{
	if (comp->funcs && comp->funcs->enable_vblank)
		comp->funcs->enable_vblank(comp, crtc);
}