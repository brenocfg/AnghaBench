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
typedef  int u64 ;
typedef  int u32 ;
struct hibmc_framebuffer {int /*<<< orphan*/  obj; } ;
struct hibmc_drm_private {scalar_t__ mmio; } ;
struct hibmc_bo {int /*<<< orphan*/  bo; } ;
struct drm_plane_state {TYPE_3__* fb; } ;
struct drm_plane {TYPE_1__* dev; struct drm_plane_state* state; } ;
struct TYPE_6__ {int width; TYPE_2__* format; } ;
struct TYPE_5__ {int* cpp; } ;
struct TYPE_4__ {struct hibmc_drm_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ HIBMC_CRT_DISP_CTL ; 
 int /*<<< orphan*/  HIBMC_CRT_DISP_CTL_FORMAT ; 
 int HIBMC_CRT_DISP_CTL_FORMAT_MASK ; 
 scalar_t__ HIBMC_CRT_FB_ADDRESS ; 
 scalar_t__ HIBMC_CRT_FB_WIDTH ; 
 int /*<<< orphan*/  HIBMC_CRT_FB_WIDTH_OFFS ; 
 int /*<<< orphan*/  HIBMC_CRT_FB_WIDTH_WIDTH ; 
 int HIBMC_FIELD (int /*<<< orphan*/ ,int) ; 
 void* PADDING (int,unsigned int) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 struct hibmc_bo* gem_to_hibmc_bo (int /*<<< orphan*/ ) ; 
 int hibmc_bo_pin (struct hibmc_bo*,int /*<<< orphan*/ ,int*) ; 
 int readl (scalar_t__) ; 
 struct hibmc_framebuffer* to_hibmc_framebuffer (TYPE_3__*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void hibmc_plane_atomic_update(struct drm_plane *plane,
				      struct drm_plane_state *old_state)
{
	struct drm_plane_state	*state	= plane->state;
	u32 reg;
	int ret;
	u64 gpu_addr = 0;
	unsigned int line_l;
	struct hibmc_drm_private *priv = plane->dev->dev_private;
	struct hibmc_framebuffer *hibmc_fb;
	struct hibmc_bo *bo;

	if (!state->fb)
		return;

	hibmc_fb = to_hibmc_framebuffer(state->fb);
	bo = gem_to_hibmc_bo(hibmc_fb->obj);
	ret = ttm_bo_reserve(&bo->bo, true, false, NULL);
	if (ret) {
		DRM_ERROR("failed to reserve ttm_bo: %d", ret);
		return;
	}

	ret = hibmc_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	ttm_bo_unreserve(&bo->bo);
	if (ret) {
		DRM_ERROR("failed to pin hibmc_bo: %d", ret);
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