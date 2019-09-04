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
struct TYPE_5__ {int /*<<< orphan*/  nvbo; } ;
struct TYPE_4__ {scalar_t__ depth; } ;
struct nouveau_crtc {int index; TYPE_2__ cursor; int /*<<< orphan*/  base; int /*<<< orphan*/  restore; int /*<<< orphan*/  save; int /*<<< orphan*/  last_dpms; TYPE_1__ lut; } ;
struct drm_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NV_DPMS_CLEARED ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  create_primary_plane (struct drm_device*) ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_init_with_planes (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_mode_crtc_set_gamma_size (int /*<<< orphan*/ *,int) ; 
 struct nouveau_crtc* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nouveau_bo_map (int /*<<< orphan*/ ) ; 
 int nouveau_bo_new (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nouveau_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nouveau_bo_ref (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nouveau_bo_unpin (int /*<<< orphan*/ ) ; 
 TYPE_3__* nouveau_drm (struct drm_device*) ; 
 int /*<<< orphan*/  nv04_crtc_funcs ; 
 int /*<<< orphan*/  nv04_crtc_helper_funcs ; 
 int /*<<< orphan*/  nv04_cursor_init (struct nouveau_crtc*) ; 
 int /*<<< orphan*/  nv_crtc_restore ; 
 int /*<<< orphan*/  nv_crtc_save ; 

int
nv04_crtc_create(struct drm_device *dev, int crtc_num)
{
	struct nouveau_crtc *nv_crtc;
	int ret;

	nv_crtc = kzalloc(sizeof(*nv_crtc), GFP_KERNEL);
	if (!nv_crtc)
		return -ENOMEM;

	nv_crtc->lut.depth = 0;

	nv_crtc->index = crtc_num;
	nv_crtc->last_dpms = NV_DPMS_CLEARED;

	nv_crtc->save = nv_crtc_save;
	nv_crtc->restore = nv_crtc_restore;

	drm_crtc_init_with_planes(dev, &nv_crtc->base,
                                  create_primary_plane(dev), NULL,
                                  &nv04_crtc_funcs, NULL);
	drm_crtc_helper_add(&nv_crtc->base, &nv04_crtc_helper_funcs);
	drm_mode_crtc_set_gamma_size(&nv_crtc->base, 256);

	ret = nouveau_bo_new(&nouveau_drm(dev)->client, 64*64*4, 0x100,
			     TTM_PL_FLAG_VRAM, 0, 0x0000, NULL, NULL,
			     &nv_crtc->cursor.nvbo);
	if (!ret) {
		ret = nouveau_bo_pin(nv_crtc->cursor.nvbo, TTM_PL_FLAG_VRAM, false);
		if (!ret) {
			ret = nouveau_bo_map(nv_crtc->cursor.nvbo);
			if (ret)
				nouveau_bo_unpin(nv_crtc->cursor.nvbo);
		}
		if (ret)
			nouveau_bo_ref(NULL, &nv_crtc->cursor.nvbo);
	}

	nv04_cursor_init(nv_crtc);

	return 0;
}