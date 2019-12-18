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
struct drm_crtc_state {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gamma_set ) (struct mtk_ddp_comp*,struct drm_crtc_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct mtk_ddp_comp*,struct drm_crtc_state*) ; 

__attribute__((used)) static inline void mtk_ddp_gamma_set(struct mtk_ddp_comp *comp,
				     struct drm_crtc_state *state)
{
	if (comp->funcs && comp->funcs->gamma_set)
		comp->funcs->gamma_set(comp, state);
}