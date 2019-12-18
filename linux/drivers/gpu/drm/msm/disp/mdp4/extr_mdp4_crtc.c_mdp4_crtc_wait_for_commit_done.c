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
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdp4_crtc_wait_for_flush_done (struct drm_crtc*) ; 

void mdp4_crtc_wait_for_commit_done(struct drm_crtc *crtc)
{
	/* wait_for_flush_done is the only case for now.
	 * Later we will have command mode CRTC to wait for
	 * other event.
	 */
	mdp4_crtc_wait_for_flush_done(crtc);
}