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
struct mxsfb_drm_private {int dummy; } ;
struct drm_simple_display_pipe {int dummy; } ;
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 struct mxsfb_drm_private* drm_pipe_to_mxsfb_drm_private (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  mxsfb_plane_atomic_update (struct mxsfb_drm_private*,struct drm_plane_state*) ; 

__attribute__((used)) static void mxsfb_pipe_update(struct drm_simple_display_pipe *pipe,
			      struct drm_plane_state *plane_state)
{
	struct mxsfb_drm_private *mxsfb = drm_pipe_to_mxsfb_drm_private(pipe);

	mxsfb_plane_atomic_update(mxsfb, plane_state);
}