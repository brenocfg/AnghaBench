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
struct dc_stream_state {scalar_t__ psr_version; } ;
struct dc_info_packet {int hb0; int hb1; int hb2; int hb3; int valid; scalar_t__* sb; } ;

/* Variables and functions */

__attribute__((used)) static void set_vsc_info_packet(
		struct dc_info_packet *info_packet,
		struct dc_stream_state *stream)
{
	unsigned int vscPacketRevision = 0;
	unsigned int i;

	/*VSC packet set to 2 when DP revision >= 1.2*/
	if (stream->psr_version != 0) {
		vscPacketRevision = 2;
	}

	/* VSC packet not needed based on the features
	 * supported by this DP display
	 */
	if (vscPacketRevision == 0)
		return;

	if (vscPacketRevision == 0x2) {
		/* Secondary-data Packet ID = 0*/
		info_packet->hb0 = 0x00;
		/* 07h - Packet Type Value indicating Video
		 * Stream Configuration packet
		 */
		info_packet->hb1 = 0x07;
		/* 02h = VSC SDP supporting 3D stereo and PSR
		 * (applies to eDP v1.3 or higher).
		 */
		info_packet->hb2 = 0x02;
		/* 08h = VSC packet supporting 3D stereo + PSR
		 * (HB2 = 02h).
		 */
		info_packet->hb3 = 0x08;

		for (i = 0; i < 28; i++)
			info_packet->sb[i] = 0;

		info_packet->valid = true;
	}

	/*TODO: stereo 3D support and extend pixel encoding colorimetry*/
}