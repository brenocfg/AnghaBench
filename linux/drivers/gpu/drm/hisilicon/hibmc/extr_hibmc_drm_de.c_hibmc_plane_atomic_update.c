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
struct hibmc_framebuffer {int /*<<< orphan*/  obj; } ;
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct drm_plane_state {TYPE_3__* fb; } ;
struct drm_plane {TYPE_1__* dev; struct drm_plane_state* state; } ;
struct drm_gem_vram_object {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_6__ {int width; TYPE_2__* format; } ;
struct TYPE_5__ {int* cpp; } ;
struct TYPE_4__ {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_GEM_VRAM_PL_FLAG_VRAM ; 
 scalar_t__ HIBMC_CRT_DISP_CTL ; 
 int /*<<< orphan*/  HIBMC_CRT_DISP_CTL_FORMAT ; 
 int HIBMC_CRT_DISP_CTL_FORMAT_MASK ; 
 scalar_t__ HIBMC_CRT_FB_ADDRESS ; 
 scalar_t__ HIBMC_CRT_FB_WIDTH ; 
 int /*<<< orphan*/  HIBMC_CRT_FB_WIDTH_OFFS ; 
 int /*<<< orphan*/  HIBMC_CRT_FB_WIDTH_WIDTH ; 
 int HIBMC_FIELD (int /*<<< orphan*/ ,int) ; 
 void* PADDING (int,unsigned int) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 
 scalar_t__ drm_gem_vram_offset (struct drm_gem_vram_object*) ; 
 int drm_gem_vram_pin (struct drm_gem_vram_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 
 int readl (scalar_t__) ; 
 struct hibmc_framebuffer* to_hibmc_framebuffer (TYPE_3__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hibmc_plane_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct drm_plane_state	*state	= plane->state;
	u32 reg;
	int ret;
	s64 gpu_addr = 0;
	unsigned int line_l;
	struct hibmc_drm_private *priv = plane->dev->dev_private;
	struct hibmc_framebuffer *hibmc_fb;
	struct drm_gem_vram_object *gbo;

	if (!state->fb)
		return;

	hibmc_fb = to_hibmc_framebuffer(state->fb);
	gbo = drm_gem_vram_of_gem(hibmc_fb->obj);

	ret = drm_gem_vram_pin(gbo, DRM_GEM_VRAM_PL_FLAG_VRAM);
	if (ret) {
		DRM_ERROR("failed to pin bo: %d", ret);
		return;
	}
	gpu_addr = drm_gem_vram_offset(gbo);
	if (gpu_addr < 0) {
		drm_gem_vram_unpin(gbo);
		return;
	}

	writel(gpu_addr, priv->mmio + HIBMC_CRT_FB_ADDRESS);

	reg = state->fb->width * (state->fb->format->cpp[0]);
	/* now line_pad is 16 */
	reg = PADDING(16, reg);

	line_l = state->fb->width * state->fb->format->cpp[0];
	line_l = PADDING(16, line_l);
	writel(HIBMC_FIELD(HIBMC_CRT_FB_WIDTH_WIDTH, reg) |
	       HIBMC_FIELD(HIBMC_CRT_FB_WIDTH_OFFS, line_l),
	       priv->mmio + HIBMC_CRT_FB_WIDTH);

	/* SET PIXEL FORMAT */
	reg = readl(priv->mmio + HIBMC_CRT_DISP_CTL);
	reg &= ~HIBMC_CRT_DISP_CTL_FORMAT_MASK;
	reg |= HIBMC_FIELD(HIBMC_CRT_DISP_CTL_FORMAT,
			   state->fb->format->cpp[0] * 8 / 16);
	writel(reg, priv->mmio + HIBMC_CRT_DISP_CTL);
}