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
struct hdmi_vendor_infoframe {scalar_t__ s3d_struct; scalar_t__ vic; } ;

/* Variables and functions */
 scalar_t__ HDMI_3D_STRUCTURE_INVALID ; 
 scalar_t__ HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 

__attribute__((used)) static int hdmi_vendor_infoframe_length(const struct hdmi_vendor_infoframe *frame)
{
	/* for side by side (half) we also need to provide 3D_Ext_Data */
	if (frame->s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
		return 6;
	else if (frame->vic != 0 || frame->s3d_struct != HDMI_3D_STRUCTURE_INVALID)
		return 5;
	else
		return 4;
}