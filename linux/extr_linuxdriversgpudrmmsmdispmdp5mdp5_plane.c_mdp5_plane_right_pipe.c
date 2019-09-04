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
struct mdp5_plane_state {TYPE_1__* r_hwpipe; } ;
struct drm_plane {int /*<<< orphan*/  state; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;
struct TYPE_2__ {int pipe; } ;

/* Variables and functions */
 int SSPP_NONE ; 
 struct mdp5_plane_state* to_mdp5_plane_state (int /*<<< orphan*/ ) ; 

enum mdp5_pipe mdp5_plane_right_pipe(struct drm_plane *plane)
{
	struct mdp5_plane_state *pstate = to_mdp5_plane_state(plane->state);

	if (!pstate->r_hwpipe)
		return SSPP_NONE;

	return pstate->r_hwpipe->pipe;
}