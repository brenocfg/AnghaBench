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
struct TYPE_2__ {int type; } ;
union hdmi_infoframe {TYPE_1__ any; } ;
typedef  int uint8_t ;
typedef  int u32 ;
struct vc4_dev {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int HDMI_READ (int) ; 
 int /*<<< orphan*/  HDMI_WRITE (int,int) ; 
 int VC4_HDMI_PACKET_STRIDE ; 
 int VC4_HDMI_RAM_PACKET (int) ; 
 int VC4_HDMI_RAM_PACKET_CONFIG ; 
 int VC4_HDMI_RAM_PACKET_ENABLE ; 
 int VC4_HDMI_RAM_PACKET_STATUS ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ hdmi_infoframe_pack (union hdmi_infoframe*,int*,int) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int vc4_hdmi_stop_packet (struct drm_encoder*,int) ; 
 int wait_for (int,int) ; 

__attribute__((used)) static void vc4_hdmi_write_infoframe(struct drm_encoder *encoder,
				     union hdmi_infoframe *frame)
{
	struct drm_device *dev = encoder->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	u32 packet_id = frame->any.type - 0x80;
	u32 packet_reg = VC4_HDMI_RAM_PACKET(packet_id);
	uint8_t buffer[VC4_HDMI_PACKET_STRIDE];
	ssize_t len, i;
	int ret;

	WARN_ONCE(!(HDMI_READ(VC4_HDMI_RAM_PACKET_CONFIG) &
		    VC4_HDMI_RAM_PACKET_ENABLE),
		  "Packet RAM has to be on to store the packet.");

	len = hdmi_infoframe_pack(frame, buffer, sizeof(buffer));
	if (len < 0)
		return;

	ret = vc4_hdmi_stop_packet(encoder, frame->any.type);
	if (ret) {
		DRM_ERROR("Failed to wait for infoframe to go idle: %d\n", ret);
		return;
	}

	for (i = 0; i < len; i += 7) {
		HDMI_WRITE(packet_reg,
			   buffer[i + 0] << 0 |
			   buffer[i + 1] << 8 |
			   buffer[i + 2] << 16);
		packet_reg += 4;

		HDMI_WRITE(packet_reg,
			   buffer[i + 3] << 0 |
			   buffer[i + 4] << 8 |
			   buffer[i + 5] << 16 |
			   buffer[i + 6] << 24);
		packet_reg += 4;
	}

	HDMI_WRITE(VC4_HDMI_RAM_PACKET_CONFIG,
		   HDMI_READ(VC4_HDMI_RAM_PACKET_CONFIG) | BIT(packet_id));
	ret = wait_for((HDMI_READ(VC4_HDMI_RAM_PACKET_STATUS) &
			BIT(packet_id)), 100);
	if (ret)
		DRM_ERROR("Failed to wait for infoframe to start: %d\n", ret);
}