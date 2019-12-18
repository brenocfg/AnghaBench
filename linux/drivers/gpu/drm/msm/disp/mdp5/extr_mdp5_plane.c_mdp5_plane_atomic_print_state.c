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
struct mdp5_plane_state {char* premultiplied; char* zpos; char* alpha; int /*<<< orphan*/  stage; TYPE_2__* r_hwpipe; TYPE_1__* hwpipe; } ;
struct mdp5_kms {int caps; } ;
struct drm_printer {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  plane; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int MDP_CAP_SRC_SPLIT ; 
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,char*) ; 
 struct mdp5_kms* get_kms (int /*<<< orphan*/ ) ; 
 char* stage2name (int /*<<< orphan*/ ) ; 
 struct mdp5_plane_state* to_mdp5_plane_state (struct drm_plane_state const*) ; 

__attribute__((used)) static void
mdp5_plane_atomic_print_state(struct drm_printer *p,
		const struct drm_plane_state *state)
{
	struct mdp5_plane_state *pstate = to_mdp5_plane_state(state);
	struct mdp5_kms *mdp5_kms = get_kms(state->plane);

	drm_printf(p, "\thwpipe=%s\n", pstate->hwpipe ?
			pstate->hwpipe->name : "(null)");
	if (mdp5_kms->caps & MDP_CAP_SRC_SPLIT)
		drm_printf(p, "\tright-hwpipe=%s\n",
			   pstate->r_hwpipe ? pstate->r_hwpipe->name :
					      "(null)");
	drm_printf(p, "\tpremultiplied=%u\n", pstate->premultiplied);
	drm_printf(p, "\tzpos=%u\n", pstate->zpos);
	drm_printf(p, "\talpha=%u\n", pstate->alpha);
	drm_printf(p, "\tstage=%s\n", stage2name(pstate->stage));
}