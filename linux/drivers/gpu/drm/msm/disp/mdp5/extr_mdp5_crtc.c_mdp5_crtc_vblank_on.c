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
struct mdp5_interface {scalar_t__ mode; } ;
struct TYPE_2__ {struct mdp5_interface* intf; } ;
struct mdp5_crtc_state {TYPE_1__ pipeline; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  drm_crtc_set_max_vblank_count (struct drm_crtc*,int) ; 
 int /*<<< orphan*/  drm_crtc_vblank_on (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp5_crtc_vblank_on(struct drm_crtc *crtc)
{
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_interface *intf = mdp5_cstate->pipeline.intf;
	u32 count;

	count = intf->mode == MDP5_INTF_DSI_MODE_COMMAND ? 0 : 0xffffffff;
	drm_crtc_set_max_vblank_count(crtc, count);

	drm_crtc_vblank_on(crtc);
}