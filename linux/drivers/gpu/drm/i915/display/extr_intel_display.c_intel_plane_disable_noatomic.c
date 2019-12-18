#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct intel_plane_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; TYPE_1__ base; int /*<<< orphan*/  state; } ;
struct intel_plane {size_t id; TYPE_2__ base; } ;
struct intel_crtc_state {scalar_t__* data_rate; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; TYPE_3__ base; int /*<<< orphan*/  state; } ;
struct intel_crtc {TYPE_4__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t PLANE_PRIMARY ; 
 int /*<<< orphan*/  fixup_active_planes (struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_disable_plane (struct intel_plane*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  intel_pre_disable_primary_noatomic (TYPE_4__*) ; 
 int /*<<< orphan*/  intel_set_plane_visible (struct intel_crtc_state*,struct intel_plane_state*,int) ; 
 struct intel_crtc_state* to_intel_crtc_state (int /*<<< orphan*/ ) ; 
 struct intel_plane_state* to_intel_plane_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_plane_disable_noatomic(struct intel_crtc *crtc,
					 struct intel_plane *plane)
{
	struct intel_crtc_state *crtc_state =
		to_intel_crtc_state(crtc->base.state);
	struct intel_plane_state *plane_state =
		to_intel_plane_state(plane->base.state);

	DRM_DEBUG_KMS("Disabling [PLANE:%d:%s] on [CRTC:%d:%s]\n",
		      plane->base.base.id, plane->base.name,
		      crtc->base.base.id, crtc->base.name);

	intel_set_plane_visible(crtc_state, plane_state, false);
	fixup_active_planes(crtc_state);
	crtc_state->data_rate[plane->id] = 0;

	if (plane->id == PLANE_PRIMARY)
		intel_pre_disable_primary_noatomic(&crtc->base);

	intel_disable_plane(plane, crtc_state);
}