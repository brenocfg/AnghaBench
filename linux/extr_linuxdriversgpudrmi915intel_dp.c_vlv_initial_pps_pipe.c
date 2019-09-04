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
typedef  int /*<<< orphan*/  (* vlv_pipe_check ) (struct drm_i915_private*,int) ;
typedef  scalar_t__ u32 ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 scalar_t__ I915_READ (int /*<<< orphan*/ ) ; 
 int INVALID_PIPE ; 
 scalar_t__ PANEL_PORT_SELECT_MASK ; 
 scalar_t__ PANEL_PORT_SELECT_VLV (int) ; 
 int PIPE_A ; 
 int PIPE_B ; 
 int /*<<< orphan*/  PP_ON_DELAYS (int) ; 

__attribute__((used)) static enum pipe
vlv_initial_pps_pipe(struct drm_i915_private *dev_priv,
		     enum port port,
		     vlv_pipe_check pipe_check)
{
	enum pipe pipe;

	for (pipe = PIPE_A; pipe <= PIPE_B; pipe++) {
		u32 port_sel = I915_READ(PP_ON_DELAYS(pipe)) &
			PANEL_PORT_SELECT_MASK;

		if (port_sel != PANEL_PORT_SELECT_VLV(port))
			continue;

		if (!pipe_check(dev_priv, pipe))
			continue;

		return pipe;
	}

	return INVALID_PIPE;
}