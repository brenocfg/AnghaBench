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
struct hdmi_vendor_infoframe {scalar_t__ type; int version; scalar_t__ oui; scalar_t__ vic; scalar_t__ s3d_struct; scalar_t__ length; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HDMI_3D_STRUCTURE_INVALID ; 
 scalar_t__ HDMI_IEEE_OUI ; 
 scalar_t__ HDMI_INFOFRAME_TYPE_VENDOR ; 
 scalar_t__ hdmi_vendor_infoframe_length (struct hdmi_vendor_infoframe const*) ; 

__attribute__((used)) static int hdmi_vendor_infoframe_check_only(const struct hdmi_vendor_infoframe *frame)
{
	if (frame->type != HDMI_INFOFRAME_TYPE_VENDOR ||
	    frame->version != 1 ||
	    frame->oui != HDMI_IEEE_OUI)
		return -EINVAL;

	/* only one of those can be supplied */
	if (frame->vic != 0 && frame->s3d_struct != HDMI_3D_STRUCTURE_INVALID)
		return -EINVAL;

	if (frame->length != hdmi_vendor_infoframe_length(frame))
		return -EINVAL;

	return 0;
}