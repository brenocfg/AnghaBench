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
struct TYPE_2__ {scalar_t__ flags; int /*<<< orphan*/  func; } ;
struct wait_rps_boost {TYPE_1__ wait; struct drm_crtc* crtc; int /*<<< orphan*/  request; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTEL_GEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_i915 (struct dma_fence*) ; 
 int /*<<< orphan*/  do_rps_boost ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_waitqueue (struct drm_crtc*) ; 
 struct wait_rps_boost* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_i915 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_request (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_rps_boost_after_vblank(struct drm_crtc *crtc,
				       struct dma_fence *fence)
{
	struct wait_rps_boost *wait;

	if (!dma_fence_is_i915(fence))
		return;

	if (INTEL_GEN(to_i915(crtc->dev)) < 6)
		return;

	if (drm_crtc_vblank_get(crtc))
		return;

	wait = kmalloc(sizeof(*wait), GFP_KERNEL);
	if (!wait) {
		drm_crtc_vblank_put(crtc);
		return;
	}

	wait->request = to_request(dma_fence_get(fence));
	wait->crtc = crtc;

	wait->wait.func = do_rps_boost;
	wait->wait.flags = 0;

	add_wait_queue(drm_crtc_vblank_waitqueue(crtc), &wait->wait);
}