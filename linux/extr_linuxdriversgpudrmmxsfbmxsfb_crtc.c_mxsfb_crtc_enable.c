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

/* Variables and functions */
 int /*<<< orphan*/  mxsfb_crtc_mode_set_nofb (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_controller (struct mxsfb_drm_private*) ; 

void mxsfb_crtc_enable(struct mxsfb_drm_private *mxsfb)
{
	mxsfb_crtc_mode_set_nofb(mxsfb);
	mxsfb_enable_controller(mxsfb);
}