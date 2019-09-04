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
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_MISCCTL ; 
 int OSD_MISCCTL_RGBEN ; 
 int OSD_MISCCTL_RGBWIN ; 
 scalar_t__ VPBE_VERSION_1 ; 
 int WIN_VID0 ; 
 int WIN_VID1 ; 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_enable_vid_rgb888(struct osd_state *sd,
				   enum osd_layer layer)
{
	/*
	 * The DM6446 supports RGB888 pixel format in a single video window.
	 * This routine enables RGB888 pixel format for the specified video
	 * window.  The caller must ensure that the other video window is not
	 * currently configured for RGB888 pixel format, as this routine will
	 * disable RGB888 pixel format for the other window.
	 */
	if (sd->vpbe_type == VPBE_VERSION_1) {
		if (layer == WIN_VID0)
			osd_modify(sd, OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL_RGBEN, OSD_MISCCTL);
		else if (layer == WIN_VID1)
			osd_modify(sd, OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL_RGBEN | OSD_MISCCTL_RGBWIN,
				  OSD_MISCCTL);
	}
}