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
struct stream_encoder {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  HDMI_GENERIC0_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC0_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC0_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC1_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC1_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC1_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC2_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC2_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC2_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC3_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC3_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC3_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC4_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC4_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC4_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC5_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC5_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC5_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC6_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC6_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC6_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC7_CONT ; 
 int /*<<< orphan*/  HDMI_GENERIC7_LINE ; 
 int /*<<< orphan*/  HDMI_GENERIC7_SEND ; 
 int /*<<< orphan*/  HDMI_GENERIC_PACKET_CONTROL0 ; 
 int /*<<< orphan*/  HDMI_GENERIC_PACKET_CONTROL1 ; 
 int /*<<< orphan*/  HDMI_GENERIC_PACKET_CONTROL2 ; 
 int /*<<< orphan*/  HDMI_GENERIC_PACKET_CONTROL3 ; 
 int /*<<< orphan*/  HDMI_GENERIC_PACKET_CONTROL4 ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enc2_stream_encoder_stop_hdmi_info_packets(
	struct stream_encoder *enc)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* stop generic packets 0,1 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC0_CONT, 0,
		HDMI_GENERIC0_SEND, 0,
		HDMI_GENERIC1_CONT, 0,
		HDMI_GENERIC1_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL1, 0,
		HDMI_GENERIC0_LINE, 0,
		HDMI_GENERIC1_LINE, 0);

	/* stop generic packets 2,3 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC2_CONT, 0,
		HDMI_GENERIC2_SEND, 0,
		HDMI_GENERIC3_CONT, 0,
		HDMI_GENERIC3_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL2, 0,
		HDMI_GENERIC2_LINE, 0,
		HDMI_GENERIC3_LINE, 0);

	/* stop generic packets 4,5 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC4_CONT, 0,
		HDMI_GENERIC4_SEND, 0,
		HDMI_GENERIC5_CONT, 0,
		HDMI_GENERIC5_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL3, 0,
		HDMI_GENERIC4_LINE, 0,
		HDMI_GENERIC5_LINE, 0);

	/* stop generic packets 6,7 on HDMI */
	REG_SET_4(HDMI_GENERIC_PACKET_CONTROL0, 0,
		HDMI_GENERIC6_CONT, 0,
		HDMI_GENERIC6_SEND, 0,
		HDMI_GENERIC7_CONT, 0,
		HDMI_GENERIC7_SEND, 0);
	REG_SET_2(HDMI_GENERIC_PACKET_CONTROL4, 0,
		HDMI_GENERIC6_LINE, 0,
		HDMI_GENERIC7_LINE, 0);
}