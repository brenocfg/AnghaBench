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
struct mod_vrr_params {int /*<<< orphan*/  send_info_frame; int /*<<< orphan*/  supported; } ;
struct mod_freesync {int dummy; } ;
struct dc_stream_state {int /*<<< orphan*/  signal; } ;
struct dc_info_packet {int dummy; } ;
typedef  enum vrr_packet_type { ____Placeholder_vrr_packet_type } vrr_packet_type ;
typedef  enum color_transfer_func { ____Placeholder_color_transfer_func } color_transfer_func ;

/* Variables and functions */
#define  PACKET_TYPE_FS1 130 
#define  PACKET_TYPE_FS2 129 
#define  PACKET_TYPE_VRR 128 
 int /*<<< orphan*/  build_vrr_infopacket_v1 (int /*<<< orphan*/ ,struct mod_vrr_params const*,struct dc_info_packet*) ; 
 int /*<<< orphan*/  build_vrr_infopacket_v2 (int /*<<< orphan*/ ,struct mod_vrr_params const*,int,struct dc_info_packet*) ; 

void mod_freesync_build_vrr_infopacket(struct mod_freesync *mod_freesync,
		const struct dc_stream_state *stream,
		const struct mod_vrr_params *vrr,
		enum vrr_packet_type packet_type,
		enum color_transfer_func app_tf,
		struct dc_info_packet *infopacket)
{
	/* SPD info packet for FreeSync
	 * VTEM info packet for HdmiVRR
	 * Check if Freesync is supported. Return if false. If true,
	 * set the corresponding bit in the info packet
	 */
	if (!vrr->supported || (!vrr->send_info_frame))
		return;

	switch (packet_type) {
	case PACKET_TYPE_FS2:
		build_vrr_infopacket_v2(stream->signal, vrr, app_tf, infopacket);
		break;
	case PACKET_TYPE_VRR:
	case PACKET_TYPE_FS1:
	default:
		build_vrr_infopacket_v1(stream->signal, vrr, infopacket);
	}
}