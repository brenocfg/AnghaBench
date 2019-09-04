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
struct mxsfb_drm_private {int /*<<< orphan*/  panel; } ;
struct drm_simple_display_pipe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_panel_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_panel_unprepare (int /*<<< orphan*/ ) ; 
 struct mxsfb_drm_private* drm_pipe_to_mxsfb_drm_private (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  mxsfb_crtc_disable (struct mxsfb_drm_private*) ; 

__attribute__((used)) static void mxsfb_pipe_disable(struct drm_simple_display_pipe *pipe)
{
	struct mxsfb_drm_private *mxsfb = drm_pipe_to_mxsfb_drm_private(pipe);

	drm_panel_disable(mxsfb->panel);
	mxsfb_crtc_disable(mxsfb);
	drm_panel_unprepare(mxsfb->panel);
}