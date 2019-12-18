#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int scale; int blend; int point; int /*<<< orphan*/  image; } ;
struct TYPE_16__ {int sx; int sy; int sw; int sh; int k1; int src_color; int dst_color; int /*<<< orphan*/  y; int /*<<< orphan*/  x; scalar_t__ depth; int /*<<< orphan*/  dh; int /*<<< orphan*/  dw; } ;
struct TYPE_15__ {int src_x; int src_y; int src_w; int src_h; int alpha; int pixel_blend_mode; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; scalar_t__ normalized_zpos; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  fb; } ;
struct TYPE_24__ {int layout; int blockh; int* blocks; int* pitch; int interval; int mode; int /*<<< orphan*/  kind; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct nv50_wndw_atom {TYPE_9__ set; TYPE_12__ point; TYPE_11__ state; TYPE_12__ blend; TYPE_12__ scale; TYPE_8__ image; int /*<<< orphan*/  visible; } ;
struct TYPE_17__ {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct nv50_wndw {TYPE_10__* func; scalar_t__ immd; TYPE_1__ plane; } ;
struct TYPE_23__ {int /*<<< orphan*/  async_flip; } ;
struct nv50_head_atom {TYPE_7__ state; } ;
struct TYPE_22__ {int* pitches; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct nouveau_framebuffer {TYPE_6__ base; TYPE_5__* nvbo; } ;
struct TYPE_18__ {int chipset; } ;
struct TYPE_19__ {TYPE_2__ info; } ;
struct TYPE_20__ {TYPE_3__ device; } ;
struct nouveau_drm {TYPE_4__ client; } ;
struct TYPE_21__ {int mode; int /*<<< orphan*/  kind; } ;
struct TYPE_14__ {int (* acquire ) (struct nv50_wndw*,struct nv50_wndw_atom*,struct nv50_head_atom*) ;scalar_t__ blend_set; scalar_t__ scale_set; int /*<<< orphan*/ * image_set; } ;

/* Variables and functions */
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int /*<<< orphan*/  NV_ATOMIC (struct nouveau_drm*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (TYPE_12__*,TYPE_12__*,int) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (int /*<<< orphan*/ ) ; 
 int nv50_wndw_atomic_check_acquire_rgb (struct nv50_wndw_atom*) ; 
 int nv50_wndw_atomic_check_acquire_yuv (struct nv50_wndw_atom*) ; 
 int stub1 (struct nv50_wndw*,struct nv50_wndw_atom*,struct nv50_head_atom*) ; 

__attribute__((used)) static int
nv50_wndw_atomic_check_acquire(struct nv50_wndw *wndw, bool modeset,
			       struct nv50_wndw_atom *armw,
			       struct nv50_wndw_atom *asyw,
			       struct nv50_head_atom *asyh)
{
	struct nouveau_framebuffer *fb = nouveau_framebuffer(asyw->state.fb);
	struct nouveau_drm *drm = nouveau_drm(wndw->plane.dev);
	int ret;

	NV_ATOMIC(drm, "%s acquire\n", wndw->plane.name);

	if (asyw->state.fb != armw->state.fb || !armw->visible || modeset) {
		asyw->image.w = fb->base.width;
		asyw->image.h = fb->base.height;
		asyw->image.kind = fb->nvbo->kind;

		ret = nv50_wndw_atomic_check_acquire_rgb(asyw);
		if (ret) {
			ret = nv50_wndw_atomic_check_acquire_yuv(asyw);
			if (ret)
				return ret;
		}

		if (asyw->image.kind) {
			asyw->image.layout = 0;
			if (drm->client.device.info.chipset >= 0xc0)
				asyw->image.blockh = fb->nvbo->mode >> 4;
			else
				asyw->image.blockh = fb->nvbo->mode;
			asyw->image.blocks[0] = fb->base.pitches[0] / 64;
			asyw->image.pitch[0] = 0;
		} else {
			asyw->image.layout = 1;
			asyw->image.blockh = 0;
			asyw->image.blocks[0] = 0;
			asyw->image.pitch[0] = fb->base.pitches[0];
		}

		if (!asyh->state.async_flip)
			asyw->image.interval = 1;
		else
			asyw->image.interval = 0;
		asyw->image.mode = asyw->image.interval ? 0 : 1;
		asyw->set.image = wndw->func->image_set != NULL;
	}

	if (wndw->func->scale_set) {
		asyw->scale.sx = asyw->state.src_x >> 16;
		asyw->scale.sy = asyw->state.src_y >> 16;
		asyw->scale.sw = asyw->state.src_w >> 16;
		asyw->scale.sh = asyw->state.src_h >> 16;
		asyw->scale.dw = asyw->state.crtc_w;
		asyw->scale.dh = asyw->state.crtc_h;
		if (memcmp(&armw->scale, &asyw->scale, sizeof(asyw->scale)))
			asyw->set.scale = true;
	}

	if (wndw->func->blend_set) {
		asyw->blend.depth = 255 - asyw->state.normalized_zpos;
		asyw->blend.k1 = asyw->state.alpha >> 8;
		switch (asyw->state.pixel_blend_mode) {
		case DRM_MODE_BLEND_PREMULTI:
			asyw->blend.src_color = 2; /* K1 */
			asyw->blend.dst_color = 7; /* NEG_K1_TIMES_SRC */
			break;
		case DRM_MODE_BLEND_COVERAGE:
			asyw->blend.src_color = 5; /* K1_TIMES_SRC */
			asyw->blend.dst_color = 7; /* NEG_K1_TIMES_SRC */
			break;
		case DRM_MODE_BLEND_PIXEL_NONE:
		default:
			asyw->blend.src_color = 2; /* K1 */
			asyw->blend.dst_color = 4; /* NEG_K1 */
			break;
		}
		if (memcmp(&armw->blend, &asyw->blend, sizeof(asyw->blend)))
			asyw->set.blend = true;
	}

	if (wndw->immd) {
		asyw->point.x = asyw->state.crtc_x;
		asyw->point.y = asyw->state.crtc_y;
		if (memcmp(&armw->point, &asyw->point, sizeof(asyw->point)))
			asyw->set.point = true;
	}

	return wndw->func->acquire(wndw, asyw, asyh);
}