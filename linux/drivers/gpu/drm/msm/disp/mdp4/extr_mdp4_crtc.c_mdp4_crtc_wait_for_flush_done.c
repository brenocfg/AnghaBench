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
struct mdp4_kms {int dummy; } ;
struct mdp4_crtc {int flushed_mask; int /*<<< orphan*/  id; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__* vblank; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDP4_OVERLAY_FLUSH ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t drm_crtc_index (struct drm_crtc*) ; 
 int drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 struct mdp4_kms* get_kms (struct drm_crtc*) ; 
 int mdp4_read (struct mdp4_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp4_crtc_wait_for_flush_done(struct drm_crtc *crtc)
{
	struct drm_device *dev = crtc->dev;
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct mdp4_kms *mdp4_kms = get_kms(crtc);
	int ret;

	ret = drm_crtc_vblank_get(crtc);
	if (ret)
		return;

	ret = wait_event_timeout(dev->vblank[drm_crtc_index(crtc)].queue,
		!(mdp4_read(mdp4_kms, REG_MDP4_OVERLAY_FLUSH) &
			mdp4_crtc->flushed_mask),
		msecs_to_jiffies(50));
	if (ret <= 0)
		dev_warn(dev->dev, "vblank time out, crtc=%d\n", mdp4_crtc->id);

	mdp4_crtc->flushed_mask = 0;

	drm_crtc_vblank_put(crtc);
}