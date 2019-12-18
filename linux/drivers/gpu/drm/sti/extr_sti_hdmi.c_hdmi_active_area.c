#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int hdisplay; scalar_t__ vdisplay; } ;
struct sti_hdmi {TYPE_1__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_ACTIVE_VID_XMAX ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_XMIN ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_YMAX ; 
 int /*<<< orphan*/  HDMI_ACTIVE_VID_YMIN ; 
 int /*<<< orphan*/  hdmi_write (struct sti_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sti_vtg_get_line_number (TYPE_1__,scalar_t__) ; 
 int /*<<< orphan*/  sti_vtg_get_pixel_number (TYPE_1__,int) ; 

__attribute__((used)) static void hdmi_active_area(struct sti_hdmi *hdmi)
{
	u32 xmin, xmax;
	u32 ymin, ymax;

	xmin = sti_vtg_get_pixel_number(hdmi->mode, 1);
	xmax = sti_vtg_get_pixel_number(hdmi->mode, hdmi->mode.hdisplay);
	ymin = sti_vtg_get_line_number(hdmi->mode, 0);
	ymax = sti_vtg_get_line_number(hdmi->mode, hdmi->mode.vdisplay - 1);

	hdmi_write(hdmi, xmin, HDMI_ACTIVE_VID_XMIN);
	hdmi_write(hdmi, xmax, HDMI_ACTIVE_VID_XMAX);
	hdmi_write(hdmi, ymin, HDMI_ACTIVE_VID_YMIN);
	hdmi_write(hdmi, ymax, HDMI_ACTIVE_VID_YMAX);
}