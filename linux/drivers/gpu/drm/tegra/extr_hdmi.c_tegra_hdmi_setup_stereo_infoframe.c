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
typedef  int /*<<< orphan*/  u8 ;
struct tegra_hdmi {int /*<<< orphan*/  dev; } ;
struct hdmi_vendor_infoframe {int /*<<< orphan*/  s3d_struct; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_3D_STRUCTURE_FRAME_PACKING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  hdmi_vendor_infoframe_init (struct hdmi_vendor_infoframe*) ; 
 scalar_t__ hdmi_vendor_infoframe_pack (struct hdmi_vendor_infoframe*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tegra_hdmi_write_infopack (struct tegra_hdmi*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void tegra_hdmi_setup_stereo_infoframe(struct tegra_hdmi *hdmi)
{
	struct hdmi_vendor_infoframe frame;
	u8 buffer[10];
	ssize_t err;

	hdmi_vendor_infoframe_init(&frame);
	frame.s3d_struct = HDMI_3D_STRUCTURE_FRAME_PACKING;

	err = hdmi_vendor_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(hdmi->dev, "failed to pack vendor infoframe: %zd\n",
			err);
		return;
	}

	tegra_hdmi_write_infopack(hdmi, buffer, err);
}