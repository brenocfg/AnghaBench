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
 int /*<<< orphan*/  OSD_EXTMODE ; 
 int /*<<< orphan*/  OSD_MISCCTL ; 
 int /*<<< orphan*/  OSD_MISCCTL_DMANG ; 
 int /*<<< orphan*/  OSD_MODE ; 
 int /*<<< orphan*/  OSD_OSDWIN0MD ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD ; 
 int /*<<< orphan*/  OSD_RECTCUR ; 
 int /*<<< orphan*/  OSD_VBNDRY ; 
 int /*<<< orphan*/  OSD_VIDWINMD ; 
 scalar_t__ VPBE_VERSION_3 ; 
 int /*<<< orphan*/  osd_write (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_init(struct osd_state *sd)
{
	osd_write(sd, 0, OSD_MODE);
	osd_write(sd, 0, OSD_VIDWINMD);
	osd_write(sd, 0, OSD_OSDWIN0MD);
	osd_write(sd, 0, OSD_OSDWIN1MD);
	osd_write(sd, 0, OSD_RECTCUR);
	osd_write(sd, 0, OSD_MISCCTL);
	if (sd->vpbe_type == VPBE_VERSION_3) {
		osd_write(sd, 0, OSD_VBNDRY);
		osd_write(sd, 0, OSD_EXTMODE);
		osd_write(sd, OSD_MISCCTL_DMANG, OSD_MISCCTL);
	}
}