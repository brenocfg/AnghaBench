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
struct osd_state {scalar_t__ vpbe_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_MISCCTL ; 
 int /*<<< orphan*/  OSD_MISCCTL_RGBEN ; 
 scalar_t__ VPBE_VERSION_1 ; 
 int /*<<< orphan*/  osd_clear (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_disable_vid_rgb888(struct osd_state *sd)
{
	/*
	 * The DM6446 supports RGB888 pixel format in a single video window.
	 * This routine disables RGB888 pixel format for both video windows.
	 * The caller must ensure that neither video window is currently
	 * configured for RGB888 pixel format.
	 */
	if (sd->vpbe_type == VPBE_VERSION_1)
		osd_clear(sd, OSD_MISCCTL_RGBEN, OSD_MISCCTL);
}