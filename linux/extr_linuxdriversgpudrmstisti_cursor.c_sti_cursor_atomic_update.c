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
typedef  int u32 ;
struct sti_plane {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int paddr; } ;
struct sti_cursor {int width; int height; int clut_paddr; scalar_t__ regs; TYPE_1__ pixmap; } ;
struct drm_plane_state {int crtc_x; int crtc_y; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_gem_cma_object {scalar_t__ vaddr; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_display_mode {int vdisplay; int hdisplay; } ;
struct drm_crtc {struct drm_display_mode mode; } ;

/* Variables and functions */
 scalar_t__ CUR_AWE ; 
 scalar_t__ CUR_AWS ; 
 scalar_t__ CUR_CML ; 
 scalar_t__ CUR_CTL ; 
 int CUR_CTL_CLUT_UPDATE ; 
 scalar_t__ CUR_PML ; 
 scalar_t__ CUR_PMP ; 
 scalar_t__ CUR_SIZE ; 
 scalar_t__ CUR_VPO ; 
 int /*<<< orphan*/  STI_PLANE_UPDATED ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_cursor_argb8888_to_clut8 (struct sti_cursor*,int*) ; 
 int /*<<< orphan*/  sti_plane_update_fps (struct sti_plane*,int,int) ; 
 int sti_vtg_get_line_number (struct drm_display_mode,int) ; 
 int sti_vtg_get_pixel_number (struct drm_display_mode,int) ; 
 struct sti_cursor* to_sti_cursor (struct sti_plane*) ; 
 struct sti_plane* to_sti_plane (struct drm_plane*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void sti_cursor_atomic_update(struct drm_plane *drm_plane,
				     struct drm_plane_state *oldstate)
{
	struct drm_plane_state *state = drm_plane->state;
	struct sti_plane *plane = to_sti_plane(drm_plane);
	struct sti_cursor *cursor = to_sti_cursor(plane);
	struct drm_crtc *crtc = state->crtc;
	struct drm_framebuffer *fb = state->fb;
	struct drm_display_mode *mode;
	int dst_x, dst_y;
	struct drm_gem_cma_object *cma_obj;
	u32 y, x;
	u32 val;

	if (!crtc || !fb)
		return;

	mode = &crtc->mode;
	dst_x = state->crtc_x;
	dst_y = state->crtc_y;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);

	/* Convert ARGB8888 to CLUT8 */
	sti_cursor_argb8888_to_clut8(cursor, (u32 *)cma_obj->vaddr);

	/* AWS and AWE depend on the mode */
	y = sti_vtg_get_line_number(*mode, 0);
	x = sti_vtg_get_pixel_number(*mode, 0);
	val = y << 16 | x;
	writel(val, cursor->regs + CUR_AWS);
	y = sti_vtg_get_line_number(*mode, mode->vdisplay - 1);
	x = sti_vtg_get_pixel_number(*mode, mode->hdisplay - 1);
	val = y << 16 | x;
	writel(val, cursor->regs + CUR_AWE);

	/* Set memory location, size, and position */
	writel(cursor->pixmap.paddr, cursor->regs + CUR_PML);
	writel(cursor->width, cursor->regs + CUR_PMP);
	writel(cursor->height << 16 | cursor->width, cursor->regs + CUR_SIZE);

	y = sti_vtg_get_line_number(*mode, dst_y);
	x = sti_vtg_get_pixel_number(*mode, dst_x);
	writel((y << 16) | x, cursor->regs + CUR_VPO);

	/* Set and fetch CLUT */
	writel(cursor->clut_paddr, cursor->regs + CUR_CML);
	writel(CUR_CTL_CLUT_UPDATE, cursor->regs + CUR_CTL);

	sti_plane_update_fps(plane, true, false);

	plane->status = STI_PLANE_UPDATED;
}