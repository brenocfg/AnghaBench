#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mdp4_crtc {int /*<<< orphan*/  unref_cursor_work; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_cleanup (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_flip_work_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mdp4_crtc*) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void mdp4_crtc_destroy(struct drm_crtc *crtc)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);

	drm_crtc_cleanup(crtc);
	drm_flip_work_cleanup(&mdp4_crtc->unref_cursor_work);

	kfree(mdp4_crtc);
}