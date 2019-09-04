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
struct skl_pipe_wm {int dummy; } ;
struct skl_ddb_allocation {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (struct skl_pipe_wm const*,struct skl_pipe_wm*,int) ; 
 int skl_build_pipe_wm (struct intel_crtc_state*,struct skl_ddb_allocation*,struct skl_pipe_wm*) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int skl_update_pipe_wm(struct drm_crtc_state *cstate,
			      const struct skl_pipe_wm *old_pipe_wm,
			      struct skl_pipe_wm *pipe_wm, /* out */
			      struct skl_ddb_allocation *ddb, /* out */
			      bool *changed /* out */)
{
	struct intel_crtc_state *intel_cstate = to_intel_crtc_state(cstate);
	int ret;

	ret = skl_build_pipe_wm(intel_cstate, ddb, pipe_wm);
	if (ret)
		return ret;

	if (!memcmp(old_pipe_wm, pipe_wm, sizeof(*pipe_wm)))
		*changed = false;
	else
		*changed = true;

	return 0;
}