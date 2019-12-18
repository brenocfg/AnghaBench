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
typedef  int /*<<< orphan*/  u32 ;
struct osd_state {int dummy; } ;
typedef  enum osd_win_layer { ____Placeholder_osd_win_layer } osd_win_layer ;
typedef  enum osd_clut { ____Placeholder_osd_clut } osd_clut ;

/* Variables and functions */
#define  OSDWIN_OSD0 129 
#define  OSDWIN_OSD1 128 
 int /*<<< orphan*/  OSD_OSDWIN0MD ; 
 int /*<<< orphan*/  OSD_OSDWIN0MD_CLUTS0 ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD ; 
 int /*<<< orphan*/  OSD_OSDWIN1MD_CLUTS1 ; 
 int RAM_CLUT ; 
 int /*<<< orphan*/  osd_modify (struct osd_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _osd_set_osd_clut(struct osd_state *sd,
			      enum osd_win_layer osdwin,
			      enum osd_clut clut)
{
	u32 winmd = 0;

	switch (osdwin) {
	case OSDWIN_OSD0:
		if (clut == RAM_CLUT)
			winmd |= OSD_OSDWIN0MD_CLUTS0;
		osd_modify(sd, OSD_OSDWIN0MD_CLUTS0, winmd, OSD_OSDWIN0MD);
		break;
	case OSDWIN_OSD1:
		if (clut == RAM_CLUT)
			winmd |= OSD_OSDWIN1MD_CLUTS1;
		osd_modify(sd, OSD_OSDWIN1MD_CLUTS1, winmd, OSD_OSDWIN1MD);
		break;
	}
}