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
struct encoder_info_frame {int /*<<< orphan*/  hdrsmd; int /*<<< orphan*/  spd; int /*<<< orphan*/  vendor; int /*<<< orphan*/  gamut; int /*<<< orphan*/  hfvsif; int /*<<< orphan*/  avi; } ;
struct dcn10_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  HDMI_DB_CONTROL ; 
 int /*<<< orphan*/  HDMI_DB_DISABLE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enc2_update_hdmi_info_packet (struct dcn10_stream_encoder*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enc2_stream_encoder_update_hdmi_info_packets(
	struct stream_encoder *enc,
	const struct encoder_info_frame *info_frame)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	/* for bring up, disable dp double  TODO */
	REG_UPDATE(HDMI_DB_CONTROL, HDMI_DB_DISABLE, 1);

	/*Always add mandatory packets first followed by optional ones*/
	enc2_update_hdmi_info_packet(enc1, 0, &info_frame->avi);
	enc2_update_hdmi_info_packet(enc1, 5, &info_frame->hfvsif);
	enc2_update_hdmi_info_packet(enc1, 2, &info_frame->gamut);
	enc2_update_hdmi_info_packet(enc1, 1, &info_frame->vendor);
	enc2_update_hdmi_info_packet(enc1, 3, &info_frame->spd);
	enc2_update_hdmi_info_packet(enc1, 4, &info_frame->hdrsmd);
}