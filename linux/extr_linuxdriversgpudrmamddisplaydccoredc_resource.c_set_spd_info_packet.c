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
struct TYPE_2__ {int supported; int enabled; int active; int min_refresh_in_micro_hz; int nominal_refresh_in_micro_hz; } ;
struct dc_stream_state {TYPE_1__ freesync_ctx; int /*<<< orphan*/  signal; } ;
struct dc_info_packet {int hb0; int hb1; int hb2; int hb3; int* sb; int valid; } ;

/* Variables and functions */
 void* HDMI_INFOFRAME_TYPE_SPD ; 
 scalar_t__ dc_is_dp_signal (int /*<<< orphan*/ ) ; 
 scalar_t__ dc_is_hdmi_signal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_spd_info_packet(
		struct dc_info_packet *info_packet,
		struct dc_stream_state *stream)
{
	/* SPD info packet for FreeSync */

	unsigned char checksum = 0;
	unsigned int idx, payload_size = 0;

	/* Check if Freesync is supported. Return if false. If true,
	 * set the corresponding bit in the info packet
	 */
	if (stream->freesync_ctx.supported == false)
		return;

	if (dc_is_hdmi_signal(stream->signal)) {

		/* HEADER */

		/* HB0  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		info_packet->hb0 = HDMI_INFOFRAME_TYPE_SPD;

		/* HB1  = Version = 0x01 */
		info_packet->hb1 = 0x01;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Length = 0x08] */
		info_packet->hb2 = 0x08;

		payload_size = 0x08;

	} else if (dc_is_dp_signal(stream->signal)) {

		/* HEADER */

		/* HB0  = Secondary-data Packet ID = 0 - Only non-zero
		 *	  when used to associate audio related info packets
		 */
		info_packet->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		info_packet->hb1 = HDMI_INFOFRAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Least significant eight bits -
		 *	  For INFOFRAME, the value must be 1Bh]
		 */
		info_packet->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFRAME SDP Version Number = 0x1]
		 *	  [Bits 1:0 = Most significant two bits = 0x00]
		 */
		info_packet->hb3 = 0x04;

		payload_size = 0x1B;
	}

	/* PB1 = 0x1A (24bit AMD IEEE OUI (0x00001A) - Byte 0) */
	info_packet->sb[1] = 0x1A;

	/* PB2 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 1) */
	info_packet->sb[2] = 0x00;

	/* PB3 = 0x00 (24bit AMD IEEE OUI (0x00001A) - Byte 2) */
	info_packet->sb[3] = 0x00;

	/* PB4 = Reserved */
	info_packet->sb[4] = 0x00;

	/* PB5 = Reserved */
	info_packet->sb[5] = 0x00;

	/* PB6 = [Bits 7:3 = Reserved] */
	info_packet->sb[6] = 0x00;

	if (stream->freesync_ctx.supported == true)
		/* PB6 = [Bit 0 = FreeSync Supported] */
		info_packet->sb[6] |= 0x01;

	if (stream->freesync_ctx.enabled == true)
		/* PB6 = [Bit 1 = FreeSync Enabled] */
		info_packet->sb[6] |= 0x02;

	if (stream->freesync_ctx.active == true)
		/* PB6 = [Bit 2 = FreeSync Active] */
		info_packet->sb[6] |= 0x04;

	/* PB7 = FreeSync Minimum refresh rate (Hz) */
	info_packet->sb[7] = (unsigned char) (stream->freesync_ctx.
			min_refresh_in_micro_hz / 1000000);

	/* PB8 = FreeSync Maximum refresh rate (Hz)
	 *
	 * Note: We do not use the maximum capable refresh rate
	 * of the panel, because we should never go above the field
	 * rate of the mode timing set.
	 */
	info_packet->sb[8] = (unsigned char) (stream->freesync_ctx.
			nominal_refresh_in_micro_hz / 1000000);

	/* PB9 - PB27  = Reserved */
	for (idx = 9; idx <= 27; idx++)
		info_packet->sb[idx] = 0x00;

	/* Calculate checksum */
	checksum += info_packet->hb0;
	checksum += info_packet->hb1;
	checksum += info_packet->hb2;
	checksum += info_packet->hb3;

	for (idx = 1; idx <= payload_size; idx++)
		checksum += info_packet->sb[idx];

	/* PB0 = Checksum (one byte complement) */
	info_packet->sb[0] = (unsigned char) (0x100 - checksum);

	info_packet->valid = true;
}