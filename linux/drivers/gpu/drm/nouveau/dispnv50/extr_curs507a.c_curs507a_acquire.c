#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ w; scalar_t__ h; } ;
struct TYPE_8__ {int /*<<< orphan*/  visible; int /*<<< orphan*/  crtc; } ;
struct nv50_wndw_atom {TYPE_2__ image; TYPE_4__ state; } ;
struct nv50_wndw {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  visible; } ;
struct nv50_head_atom {TYPE_1__ curs; int /*<<< orphan*/  state; } ;
struct nv50_head {TYPE_3__* func; } ;
struct TYPE_7__ {int (* curs_layout ) (struct nv50_head*,struct nv50_wndw_atom*,struct nv50_head_atom*) ;int (* curs_format ) (struct nv50_head*,struct nv50_wndw_atom*,struct nv50_head_atom*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int drm_atomic_helper_check_plane_state (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct nv50_head* nv50_head (int /*<<< orphan*/ ) ; 
 int stub1 (struct nv50_head*,struct nv50_wndw_atom*,struct nv50_head_atom*) ; 
 int stub2 (struct nv50_head*,struct nv50_wndw_atom*,struct nv50_head_atom*) ; 

__attribute__((used)) static int
curs507a_acquire(struct nv50_wndw *wndw, struct nv50_wndw_atom *asyw,
		 struct nv50_head_atom *asyh)
{
	struct nv50_head *head = nv50_head(asyw->state.crtc);
	int ret;

	ret = drm_atomic_helper_check_plane_state(&asyw->state, &asyh->state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  true, true);
	asyh->curs.visible = asyw->state.visible;
	if (ret || !asyh->curs.visible)
		return ret;

	if (asyw->image.w != asyw->image.h)
		return -EINVAL;

	ret = head->func->curs_layout(head, asyw, asyh);
	if (ret)
		return ret;

	return head->func->curs_format(head, asyw, asyh);
}