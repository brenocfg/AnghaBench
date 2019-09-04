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
typedef  union hdmi_infoframe {int dummy; } hdmi_infoframe ;
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct inno_hdmi {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  packed_frame ;

/* Variables and functions */
 scalar_t__ HDMI_CONTROL_PACKET_ADDR ; 
 scalar_t__ HDMI_CONTROL_PACKET_BUF_INDEX ; 
 int HDMI_MAXIMUM_INFO_FRAME_SIZE ; 
 int /*<<< orphan*/  HDMI_PACKET_SEND_AUTO ; 
 scalar_t__ hdmi_infoframe_pack (union hdmi_infoframe*,scalar_t__*,int) ; 
 int /*<<< orphan*/  hdmi_modb (struct inno_hdmi*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hdmi_writeb (struct inno_hdmi*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int inno_hdmi_upload_frame(struct inno_hdmi *hdmi, int setup_rc,
				  union hdmi_infoframe *frame, u32 frame_index,
				  u32 mask, u32 disable, u32 enable)
{
	if (mask)
		hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, disable);

	hdmi_writeb(hdmi, HDMI_CONTROL_PACKET_BUF_INDEX, frame_index);

	if (setup_rc >= 0) {
		u8 packed_frame[HDMI_MAXIMUM_INFO_FRAME_SIZE];
		ssize_t rc, i;

		rc = hdmi_infoframe_pack(frame, packed_frame,
					 sizeof(packed_frame));
		if (rc < 0)
			return rc;

		for (i = 0; i < rc; i++)
			hdmi_writeb(hdmi, HDMI_CONTROL_PACKET_ADDR + i,
				    packed_frame[i]);

		if (mask)
			hdmi_modb(hdmi, HDMI_PACKET_SEND_AUTO, mask, enable);
	}

	return setup_rc;
}