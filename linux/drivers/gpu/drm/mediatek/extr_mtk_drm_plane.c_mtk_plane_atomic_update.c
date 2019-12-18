#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int enable; unsigned int pitch; unsigned int format; int addr; int dirty; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct mtk_plane_state {TYPE_3__ pending; } ;
struct mtk_drm_gem_obj {int dma_addr; } ;
struct drm_plane_state {int dummy; } ;
struct drm_plane {TYPE_4__* state; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {unsigned int* pitches; TYPE_1__* format; struct drm_gem_object** obj; } ;
struct drm_crtc {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_11__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  x1; } ;
struct TYPE_8__ {int x1; int y1; } ;
struct TYPE_10__ {TYPE_5__ dst; TYPE_2__ src; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct TYPE_7__ {unsigned int format; int* cpp; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_rect_height (TYPE_5__*) ; 
 int /*<<< orphan*/  drm_rect_width (TYPE_5__*) ; 
 struct mtk_drm_gem_obj* to_mtk_gem_obj (struct drm_gem_object*) ; 
 struct mtk_plane_state* to_mtk_plane_state (TYPE_4__*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mtk_plane_atomic_update(struct drm_plane *plane,
				    struct drm_plane_state *old_state)
{
	struct mtk_plane_state *state = to_mtk_plane_state(plane->state);
	struct drm_crtc *crtc = plane->state->crtc;
	struct drm_framebuffer *fb = plane->state->fb;
	struct drm_gem_object *gem;
	struct mtk_drm_gem_obj *mtk_gem;
	unsigned int pitch, format;
	dma_addr_t addr;

	if (!crtc || WARN_ON(!fb))
		return;

	gem = fb->obj[0];
	mtk_gem = to_mtk_gem_obj(gem);
	addr = mtk_gem->dma_addr;
	pitch = fb->pitches[0];
	format = fb->format->format;

	addr += (plane->state->src.x1 >> 16) * fb->format->cpp[0];
	addr += (plane->state->src.y1 >> 16) * pitch;

	state->pending.enable = true;
	state->pending.pitch = pitch;
	state->pending.format = format;
	state->pending.addr = addr;
	state->pending.x = plane->state->dst.x1;
	state->pending.y = plane->state->dst.y1;
	state->pending.width = drm_rect_width(&plane->state->dst);
	state->pending.height = drm_rect_height(&plane->state->dst);
	wmb(); /* Make sure the above parameters are set before update */
	state->pending.dirty = true;
}