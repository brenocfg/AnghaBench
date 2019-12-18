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
struct mdp5_crtc {int /*<<< orphan*/  pp_completion; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void request_pp_done_pending(struct drm_crtc *crtc)
{
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	reinit_completion(&mdp5_crtc->pp_completion);
}