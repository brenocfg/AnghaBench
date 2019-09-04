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
typedef  int u8 ;
struct hdmi_vendor_infoframe {scalar_t__ s3d_struct; } ;
struct dw_hdmi {int /*<<< orphan*/  dev; int /*<<< orphan*/  connector; } ;
struct drm_display_mode {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF ; 
 int /*<<< orphan*/  HDMI_FC_DATAUTO0 ; 
 int /*<<< orphan*/  HDMI_FC_DATAUTO0_VSD_MASK ; 
 int /*<<< orphan*/  HDMI_FC_DATAUTO0_VSD_OFFSET ; 
 int /*<<< orphan*/  HDMI_FC_DATAUTO1 ; 
 int /*<<< orphan*/  HDMI_FC_DATAUTO2 ; 
 int /*<<< orphan*/  HDMI_FC_VSDIEEEID0 ; 
 int /*<<< orphan*/  HDMI_FC_VSDIEEEID1 ; 
 int /*<<< orphan*/  HDMI_FC_VSDIEEEID2 ; 
 int /*<<< orphan*/  HDMI_FC_VSDPAYLOAD0 ; 
 int /*<<< orphan*/  HDMI_FC_VSDPAYLOAD1 ; 
 int /*<<< orphan*/  HDMI_FC_VSDPAYLOAD2 ; 
 int /*<<< orphan*/  HDMI_FC_VSDSIZE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ drm_hdmi_vendor_infoframe_from_display_mode (struct hdmi_vendor_infoframe*,int /*<<< orphan*/ *,struct drm_display_mode*) ; 
 int /*<<< orphan*/  hdmi_mask_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hdmi_vendor_infoframe_pack (struct hdmi_vendor_infoframe*,int*,int) ; 
 int /*<<< orphan*/  hdmi_writeb (struct dw_hdmi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hdmi_config_vendor_specific_infoframe(struct dw_hdmi *hdmi,
						 struct drm_display_mode *mode)
{
	struct hdmi_vendor_infoframe frame;
	u8 buffer[10];
	ssize_t err;

	err = drm_hdmi_vendor_infoframe_from_display_mode(&frame,
							  &hdmi->connector,
							  mode);
	if (err < 0)
		/*
		 * Going into that statement does not means vendor infoframe
		 * fails. It just informed us that vendor infoframe is not
		 * needed for the selected mode. Only 4k or stereoscopic 3D
		 * mode requires vendor infoframe. So just simply return.
		 */
		return;

	err = hdmi_vendor_infoframe_pack(&frame, buffer, sizeof(buffer));
	if (err < 0) {
		dev_err(hdmi->dev, "Failed to pack vendor infoframe: %zd\n",
			err);
		return;
	}
	hdmi_mask_writeb(hdmi, 0, HDMI_FC_DATAUTO0, HDMI_FC_DATAUTO0_VSD_OFFSET,
			HDMI_FC_DATAUTO0_VSD_MASK);

	/* Set the length of HDMI vendor specific InfoFrame payload */
	hdmi_writeb(hdmi, buffer[2], HDMI_FC_VSDSIZE);

	/* Set 24bit IEEE Registration Identifier */
	hdmi_writeb(hdmi, buffer[4], HDMI_FC_VSDIEEEID0);
	hdmi_writeb(hdmi, buffer[5], HDMI_FC_VSDIEEEID1);
	hdmi_writeb(hdmi, buffer[6], HDMI_FC_VSDIEEEID2);

	/* Set HDMI_Video_Format and HDMI_VIC/3D_Structure */
	hdmi_writeb(hdmi, buffer[7], HDMI_FC_VSDPAYLOAD0);
	hdmi_writeb(hdmi, buffer[8], HDMI_FC_VSDPAYLOAD1);

	if (frame.s3d_struct >= HDMI_3D_STRUCTURE_SIDE_BY_SIDE_HALF)
		hdmi_writeb(hdmi, buffer[9], HDMI_FC_VSDPAYLOAD2);

	/* Packet frame interpolation */
	hdmi_writeb(hdmi, 1, HDMI_FC_DATAUTO1);

	/* Auto packets per frame and line spacing */
	hdmi_writeb(hdmi, 0x11, HDMI_FC_DATAUTO2);

	/* Configures the Frame Composer On RDRB mode */
	hdmi_mask_writeb(hdmi, 1, HDMI_FC_DATAUTO0, HDMI_FC_DATAUTO0_VSD_OFFSET,
			HDMI_FC_DATAUTO0_VSD_MASK);
}