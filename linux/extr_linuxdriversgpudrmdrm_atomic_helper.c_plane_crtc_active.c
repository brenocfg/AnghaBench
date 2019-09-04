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
struct drm_plane_state {TYPE_2__* crtc; } ;
struct TYPE_4__ {TYPE_1__* state; } ;
struct TYPE_3__ {scalar_t__ active; } ;

/* Variables and functions */

__attribute__((used)) static bool plane_crtc_active(const struct drm_plane_state *state)
{
	return state->crtc && state->crtc->state->active;
}