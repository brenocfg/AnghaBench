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
struct osd_state {int /*<<< orphan*/  vpbe_type; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;

/* Variables and functions */
#define  OSDWIN_OSD0 129 
#define  OSDWIN_OSD1 128 
 int /*<<< orphan*/  OSD_EXTMODE ; 
 int /*<<< orphan*/  OSD_EXTMODE_ATNOSD0EN ; 
 int /*<<< orphan*/  OSD_EXTMODE_ATNOSD1EN ; 
 int /*<<< orphan*/  OSD_OSDWIN0MD ; 
 int /*<<< orphan*/  OSD_OSDWIN0MD_ATN0E ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD_ATN1E ; 
 int /*<<< orphan*/  VPBE_VERSION_1 ; 
 int /*<<< orphan*/  VPBE_VERSION_2 ; 
 int /*<<< orphan*/  VPBE_VERSION_3 ; 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_rec601_attenuation(struct osd_state *sd,
					enum osd_win_layer osdwin, int enable)
{
	switch (osdwin) {
	case OSDWIN_OSD0:
		osd_modify(sd, OSD_OSDWIN0MD_ATN0E,
			  enable ? OSD_OSDWIN0MD_ATN0E : 0,
			  OSD_OSDWIN0MD);
		if (sd->vpbe_type == VPBE_VERSION_1)
			osd_modify(sd, OSD_OSDWIN0MD_ATN0E,
				  enable ? OSD_OSDWIN0MD_ATN0E : 0,
				  OSD_OSDWIN0MD);
		else if ((sd->vpbe_type == VPBE_VERSION_3) ||
			   (sd->vpbe_type == VPBE_VERSION_2))
			osd_modify(sd, OSD_EXTMODE_ATNOSD0EN,
				  enable ? OSD_EXTMODE_ATNOSD0EN : 0,
				  OSD_EXTMODE);
		break;
	case OSDWIN_OSD1:
		osd_modify(sd, OSD_OSDWIN1MD_ATN1E,
			  enable ? OSD_OSDWIN1MD_ATN1E : 0,
			  OSD_OSDWIN1MD);
		if (sd->vpbe_type == VPBE_VERSION_1)
			osd_modify(sd, OSD_OSDWIN1MD_ATN1E,
				  enable ? OSD_OSDWIN1MD_ATN1E : 0,
				  OSD_OSDWIN1MD);
		else if ((sd->vpbe_type == VPBE_VERSION_3) ||
			   (sd->vpbe_type == VPBE_VERSION_2))
			osd_modify(sd, OSD_EXTMODE_ATNOSD1EN,
				  enable ? OSD_EXTMODE_ATNOSD1EN : 0,
				  OSD_EXTMODE);
		break;
	}
}