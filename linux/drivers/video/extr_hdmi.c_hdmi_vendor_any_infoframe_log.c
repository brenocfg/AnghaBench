#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ oui; } ;
struct hdmi_vendor_infoframe {scalar_t__ vic; scalar_t__ s3d_struct; scalar_t__ s3d_ext_data; } ;
union hdmi_vendor_any_infoframe {TYPE_1__ any; struct hdmi_vendor_infoframe hdmi; } ;
struct hdmi_any_infoframe {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDMI_3D_STRUCTURE_INVALID ; 
 scalar_t__ HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 
 scalar_t__ HDMI_IEEE_OUI ; 
 scalar_t__ hdmi_3d_structure_get_name (scalar_t__) ; 
 int /*<<< orphan*/  hdmi_infoframe_log_header (char const*,struct device*,struct hdmi_any_infoframe const*) ; 
 int /*<<< orphan*/  hdmi_log (char*,...) ; 

__attribute__((used)) static void
hdmi_vendor_any_infoframe_log(const char *level,
			      struct device *dev,
			      const union hdmi_vendor_any_infoframe *frame)
{
	const struct hdmi_vendor_infoframe *hvf = &frame->hdmi;

	hdmi_infoframe_log_header(level, dev,
				  (const struct hdmi_any_infoframe *)frame);

	if (frame->any.oui != HDMI_IEEE_OUI) {
		hdmi_log("    not a HDMI vendor infoframe\n");
		return;
	}
	if (hvf->vic == 0 && hvf->s3d_struct == HDMI_3D_STRUCTURE_INVALID) {
		hdmi_log("    empty frame\n");
		return;
	}

	if (hvf->vic)
		hdmi_log("    HDMI VIC: %u\n", hvf->vic);
	if (hvf->s3d_struct != HDMI_3D_STRUCTURE_INVALID) {
		hdmi_log("    3D structure: %s\n",
				hdmi_3d_structure_get_name(hvf->s3d_struct));
		if (hvf->s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
			hdmi_log("    3D extension data: %d\n",
					hvf->s3d_ext_data);
	}
}