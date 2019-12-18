#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  handle; } ;
struct nv50_wndw_ctxdma {TYPE_2__ object; } ;
struct TYPE_15__ {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; int /*<<< orphan*/  fence; int /*<<< orphan*/  fb; } ;
struct TYPE_13__ {int /*<<< orphan*/ * offset; int /*<<< orphan*/ * handle; } ;
struct nv50_wndw_atom {TYPE_6__ state; TYPE_4__ image; } ;
struct TYPE_10__ {scalar_t__ parent; } ;
struct nv50_wndw {TYPE_7__* func; TYPE_1__ ctxdma; } ;
struct nv50_head_atom {TYPE_2__ object; } ;
struct nouveau_framebuffer {TYPE_8__* nvbo; } ;
struct nouveau_drm {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  resv; } ;
struct TYPE_14__ {int /*<<< orphan*/  offset; TYPE_3__ base; } ;
struct TYPE_17__ {TYPE_5__ bo; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* prepare ) (struct nv50_wndw*,struct nv50_wndw_ctxdma*,struct nv50_wndw_atom*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct nv50_wndw_ctxdma*) ; 
 int /*<<< orphan*/  NV_ATOMIC (struct nouveau_drm*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct nv50_wndw_ctxdma*) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  dma_resv_get_excl_rcu (int /*<<< orphan*/ ) ; 
 int nouveau_bo_pin (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (TYPE_8__*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (int /*<<< orphan*/ ) ; 
 struct nv50_wndw_ctxdma* nv50_head_atom_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nv50_wndw* nv50_wndw (struct drm_plane*) ; 
 struct nv50_wndw_atom* nv50_wndw_atom (struct drm_plane_state*) ; 
 struct nv50_wndw_ctxdma* nv50_wndw_ctxdma_new (struct nv50_wndw*,struct nouveau_framebuffer*) ; 
 int /*<<< orphan*/  stub1 (struct nv50_wndw*,struct nv50_wndw_ctxdma*,struct nv50_wndw_atom*) ; 

__attribute__((used)) static int
nv50_wndw_prepare_fb(struct drm_plane *plane, struct drm_plane_state *state)
{
	struct nouveau_framebuffer *fb = nouveau_framebuffer(state->fb);
	struct nouveau_drm *drm = nouveau_drm(plane->dev);
	struct nv50_wndw *wndw = nv50_wndw(plane);
	struct nv50_wndw_atom *asyw = nv50_wndw_atom(state);
	struct nv50_head_atom *asyh;
	struct nv50_wndw_ctxdma *ctxdma;
	int ret;

	NV_ATOMIC(drm, "%s prepare: %p\n", plane->name, state->fb);
	if (!asyw->state.fb)
		return 0;

	ret = nouveau_bo_pin(fb->nvbo, TTM_PL_FLAG_VRAM, true);
	if (ret)
		return ret;

	if (wndw->ctxdma.parent) {
		ctxdma = nv50_wndw_ctxdma_new(wndw, fb);
		if (IS_ERR(ctxdma)) {
			nouveau_bo_unpin(fb->nvbo);
			return PTR_ERR(ctxdma);
		}

		asyw->image.handle[0] = ctxdma->object.handle;
	}

	asyw->state.fence = dma_resv_get_excl_rcu(fb->nvbo->bo.base.resv);
	asyw->image.offset[0] = fb->nvbo->bo.offset;

	if (wndw->func->prepare) {
		asyh = nv50_head_atom_get(asyw->state.state, asyw->state.crtc);
		if (IS_ERR(asyh))
			return PTR_ERR(asyh);

		wndw->func->prepare(wndw, asyh, asyw);
	}

	return 0;
}