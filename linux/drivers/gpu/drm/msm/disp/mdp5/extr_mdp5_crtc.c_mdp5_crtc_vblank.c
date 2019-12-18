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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  irqmask; } ;
struct mdp5_crtc {TYPE_1__ vblank; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 

uint32_t mdp5_crtc_vblank(struct drm_crtc *crtc)
{
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	return mdp5_crtc->vblank.irqmask;
}