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
typedef  int u32 ;
struct osd_state {int dummy; } ;
typedef  enum osd_zoom_factor { ____Placeholder_osd_zoom_factor } osd_zoom_factor ;
typedef  enum osd_layer { ____Placeholder_osd_layer } osd_layer ;

/* Variables and functions */
 int /*<<< orphan*/  OSD_OSDWIN0MD ; 
 int OSD_OSDWIN0MD_OHZ0 ; 
 int OSD_OSDWIN0MD_OHZ0_SHIFT ; 
 int OSD_OSDWIN0MD_OVZ0 ; 
 int OSD_OSDWIN0MD_OVZ0_SHIFT ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD ; 
 int OSD_OSDWIN1MD_OHZ1 ; 
 int OSD_OSDWIN1MD_OHZ1_SHIFT ; 
 int OSD_OSDWIN1MD_OVZ1 ; 
 int OSD_OSDWIN1MD_OVZ1_SHIFT ; 
 int /*<<< orphan*/  OSD_VIDWINMD ; 
 int OSD_VIDWINMD_VHZ0 ; 
 int OSD_VIDWINMD_VHZ0_SHIFT ; 
 int OSD_VIDWINMD_VHZ1 ; 
 int OSD_VIDWINMD_VHZ1_SHIFT ; 
 int OSD_VIDWINMD_VVZ0 ; 
 int OSD_VIDWINMD_VVZ0_SHIFT ; 
 int OSD_VIDWINMD_VVZ1 ; 
 int OSD_VIDWINMD_VVZ1_SHIFT ; 
#define  WIN_OSD0 131 
#define  WIN_OSD1 130 
#define  WIN_VID0 129 
#define  WIN_VID1 128 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_zoom(struct osd_state *sd, enum osd_layer layer,
			  enum osd_zoom_factor h_zoom,
			  enum osd_zoom_factor v_zoom)
{
	u32 winmd = 0;

	switch (layer) {
	case WIN_OSD0:
		winmd |= (h_zoom << OSD_OSDWIN0MD_OHZ0_SHIFT);
		winmd |= (v_zoom << OSD_OSDWIN0MD_OVZ0_SHIFT);
		osd_modify(sd, OSD_OSDWIN0MD_OHZ0 | OSD_OSDWIN0MD_OVZ0, winmd,
			  OSD_OSDWIN0MD);
		break;
	case WIN_VID0:
		winmd |= (h_zoom << OSD_VIDWINMD_VHZ0_SHIFT);
		winmd |= (v_zoom << OSD_VIDWINMD_VVZ0_SHIFT);
		osd_modify(sd, OSD_VIDWINMD_VHZ0 | OSD_VIDWINMD_VVZ0, winmd,
			  OSD_VIDWINMD);
		break;
	case WIN_OSD1:
		winmd |= (h_zoom << OSD_OSDWIN1MD_OHZ1_SHIFT);
		winmd |= (v_zoom << OSD_OSDWIN1MD_OVZ1_SHIFT);
		osd_modify(sd, OSD_OSDWIN1MD_OHZ1 | OSD_OSDWIN1MD_OVZ1, winmd,
			  OSD_OSDWIN1MD);
		break;
	case WIN_VID1:
		winmd |= (h_zoom << OSD_VIDWINMD_VHZ1_SHIFT);
		winmd |= (v_zoom << OSD_VIDWINMD_VVZ1_SHIFT);
		osd_modify(sd, OSD_VIDWINMD_VHZ1 | OSD_VIDWINMD_VVZ1, winmd,
			  OSD_VIDWINMD);
		break;
	}
}