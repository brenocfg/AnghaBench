#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct msm_kms {int /*<<< orphan*/  aspace; } ;
struct TYPE_3__ {struct msm_kms base; } ;
struct mdp4_kms {int blank_cursor_iova; TYPE_1__ base; } ;
struct TYPE_4__ {int stale; int next_iova; int /*<<< orphan*/  lock; int /*<<< orphan*/  y; int /*<<< orphan*/  x; struct drm_gem_object* scanout_bo; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct drm_gem_object* next_bo; } ;
struct mdp4_crtc {int dma; TYPE_2__ cursor; int /*<<< orphan*/  unref_cursor_work; } ;
struct drm_gem_object {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum mdp4_dma { ____Placeholder_mdp4_dma } mdp4_dma ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_ARGB ; 
 int MDP4_DMA_CURSOR_BLEND_CONFIG_CURSOR_EN ; 
 int MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CURSOR_POS_X (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CURSOR_POS_Y (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CURSOR_SIZE_HEIGHT (int /*<<< orphan*/ ) ; 
 int MDP4_DMA_CURSOR_SIZE_WIDTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_CURSOR_BASE (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_CURSOR_BLEND_CONFIG (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_CURSOR_POS (int) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_CURSOR_SIZE (int) ; 
 int /*<<< orphan*/  drm_flip_work_queue (int /*<<< orphan*/ *,struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_get (struct drm_gem_object*) ; 
 struct mdp4_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msm_gem_get_and_pin_iova (struct drm_gem_object*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void update_cursor(struct drm_crtc *crtc)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct mdp4_kms *mdp4_kms = get_kms(crtc);
	struct msm_kms *kms = &mdp4_kms->base.base;
	enum mdp4_dma dma = mdp4_crtc->dma;
	unsigned long flags;

	spin_lock_irqsave(&mdp4_crtc->cursor.lock, flags);
	if (mdp4_crtc->cursor.stale) {
		struct drm_gem_object *next_bo = mdp4_crtc->cursor.next_bo;
		struct drm_gem_object *prev_bo = mdp4_crtc->cursor.scanout_bo;
		uint64_t iova = mdp4_crtc->cursor.next_iova;

		if (next_bo) {
			/* take a obj ref + iova ref when we start scanning out: */
			drm_gem_object_get(next_bo);
			msm_gem_get_and_pin_iova(next_bo, kms->aspace, &iova);

			/* enable cursor: */
			mdp4_write(mdp4_kms, REG_MDP4_DMA_CURSOR_SIZE(dma),
					MDP4_DMA_CURSOR_SIZE_WIDTH(mdp4_crtc->cursor.width) |
					MDP4_DMA_CURSOR_SIZE_HEIGHT(mdp4_crtc->cursor.height));
			mdp4_write(mdp4_kms, REG_MDP4_DMA_CURSOR_BASE(dma), iova);
			mdp4_write(mdp4_kms, REG_MDP4_DMA_CURSOR_BLEND_CONFIG(dma),
					MDP4_DMA_CURSOR_BLEND_CONFIG_FORMAT(CURSOR_ARGB) |
					MDP4_DMA_CURSOR_BLEND_CONFIG_CURSOR_EN);
		} else {
			/* disable cursor: */
			mdp4_write(mdp4_kms, REG_MDP4_DMA_CURSOR_BASE(dma),
					mdp4_kms->blank_cursor_iova);
		}

		/* and drop the iova ref + obj rev when done scanning out: */
		if (prev_bo)
			drm_flip_work_queue(&mdp4_crtc->unref_cursor_work, prev_bo);

		mdp4_crtc->cursor.scanout_bo = next_bo;
		mdp4_crtc->cursor.stale = false;
	}

	mdp4_write(mdp4_kms, REG_MDP4_DMA_CURSOR_POS(dma),
			MDP4_DMA_CURSOR_POS_X(mdp4_crtc->cursor.x) |
			MDP4_DMA_CURSOR_POS_Y(mdp4_crtc->cursor.y));

	spin_unlock_irqrestore(&mdp4_crtc->cursor.lock, flags);
}