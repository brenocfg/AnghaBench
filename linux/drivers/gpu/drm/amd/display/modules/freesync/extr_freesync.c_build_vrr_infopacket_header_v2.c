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
struct dc_info_packet {int hb0; int hb1; int hb2; int hb3; } ;
typedef  enum signal_type { ____Placeholder_signal_type } signal_type ;

/* Variables and functions */
 void* DC_HDMI_INFOFRAME_TYPE_SPD ; 
 scalar_t__ dc_is_dp_signal (int) ; 
 scalar_t__ dc_is_hdmi_signal (int) ; 

__attribute__((used)) static void build_vrr_infopacket_header_v2(enum signal_type signal,
		struct dc_info_packet *infopacket,
		unsigned int *payload_size)
{
	if (dc_is_hdmi_signal(signal)) {

		/* HEADER */

		/* HB0  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb0 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB1  = Version = 0x02 */
		infopacket->hb1 = 0x02;

		/* HB2  = [Bits 7:5 = 0] [Bits 4:0 = Length = 0x09] */
		infopacket->hb2 = 0x09;

		*payload_size = 0x0A;

	} else if (dc_is_dp_signal(signal)) {

		/* HEADER */

		/* HB0  = Secondary-data Packet ID = 0 - Only non-zero
		 *	  when used to associate audio related info packets
		 */
		infopacket->hb0 = 0x00;

		/* HB1  = Packet Type = 0x83 (Source Product
		 *	  Descriptor InfoFrame)
		 */
		infopacket->hb1 = DC_HDMI_INFOFRAME_TYPE_SPD;

		/* HB2  = [Bits 7:0 = Least significant eight bits -
		 *	  For INFOFRAME, the value must be 1Bh]
		 */
		infopacket->hb2 = 0x1B;

		/* HB3  = [Bits 7:2 = INFOFRAME SDP Version Number = 0x2]
		 *	  [Bits 1:0 = Most significant two bits = 0x00]
		 */
		infopacket->hb3 = 0x08;

		*payload_size = 0x1B;
	}
}