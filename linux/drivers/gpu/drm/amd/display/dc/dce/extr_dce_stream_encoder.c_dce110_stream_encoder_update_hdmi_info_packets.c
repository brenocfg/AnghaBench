#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct stream_encoder {int dummy; } ;
struct TYPE_4__ {int hb1; int /*<<< orphan*/ * sb; scalar_t__ valid; } ;
struct encoder_info_frame {TYPE_2__ hdrsmd; TYPE_2__ spd; TYPE_2__ gamut; TYPE_2__ vendor; TYPE_2__ avi; } ;
struct dce110_stream_encoder {TYPE_1__* se_mask; } ;
struct TYPE_3__ {scalar_t__ HDMI_DB_DISABLE; scalar_t__ HDMI_AVI_INFO_SEND; scalar_t__ HDMI_AVI_INFO_CONT; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFMT_AUDIO_CLOCK_EN ; 
 int /*<<< orphan*/  AFMT_AVI_INFO0 ; 
 int /*<<< orphan*/  AFMT_AVI_INFO1 ; 
 int /*<<< orphan*/  AFMT_AVI_INFO2 ; 
 int /*<<< orphan*/  AFMT_AVI_INFO3 ; 
 int /*<<< orphan*/  AFMT_AVI_INFO_VERSION ; 
 int /*<<< orphan*/  AFMT_CNTL ; 
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_CONT ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_LINE ; 
 int /*<<< orphan*/  HDMI_AVI_INFO_SEND ; 
 int /*<<< orphan*/  HDMI_DB_CONTROL ; 
 int /*<<< orphan*/  HDMI_DB_DISABLE ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL0 ; 
 int /*<<< orphan*/  HDMI_INFOFRAME_CONTROL1 ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int VBI_LINE_0 ; 
 int /*<<< orphan*/  dce110_update_hdmi_info_packet (struct dce110_stream_encoder*,int,TYPE_2__*) ; 

__attribute__((used)) static void dce110_stream_encoder_update_hdmi_info_packets(
	struct stream_encoder *enc,
	const struct encoder_info_frame *info_frame)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);

	if (enc110->se_mask->HDMI_AVI_INFO_CONT &&
			enc110->se_mask->HDMI_AVI_INFO_SEND) {

		if (info_frame->avi.valid) {
			const uint32_t *content =
				(const uint32_t *) &info_frame->avi.sb[0];
			/*we need turn on clock before programming AFMT block*/
			if (REG(AFMT_CNTL))
				REG_UPDATE(AFMT_CNTL, AFMT_AUDIO_CLOCK_EN, 1);

			REG_WRITE(AFMT_AVI_INFO0, content[0]);

			REG_WRITE(AFMT_AVI_INFO1, content[1]);

			REG_WRITE(AFMT_AVI_INFO2, content[2]);

			REG_WRITE(AFMT_AVI_INFO3, content[3]);

			REG_UPDATE(AFMT_AVI_INFO3, AFMT_AVI_INFO_VERSION,
						info_frame->avi.hb1);

			REG_UPDATE_2(HDMI_INFOFRAME_CONTROL0,
					HDMI_AVI_INFO_SEND, 1,
					HDMI_AVI_INFO_CONT, 1);

			REG_UPDATE(HDMI_INFOFRAME_CONTROL1, HDMI_AVI_INFO_LINE,
							VBI_LINE_0 + 2);

		} else {
			REG_UPDATE_2(HDMI_INFOFRAME_CONTROL0,
				HDMI_AVI_INFO_SEND, 0,
				HDMI_AVI_INFO_CONT, 0);
		}
	}

	if (enc110->se_mask->HDMI_AVI_INFO_CONT &&
			enc110->se_mask->HDMI_AVI_INFO_SEND) {
		dce110_update_hdmi_info_packet(enc110, 0, &info_frame->vendor);
		dce110_update_hdmi_info_packet(enc110, 1, &info_frame->gamut);
		dce110_update_hdmi_info_packet(enc110, 2, &info_frame->spd);
		dce110_update_hdmi_info_packet(enc110, 3, &info_frame->hdrsmd);
	}

#if defined(CONFIG_DRM_AMD_DC_DCN1_0)
	if (enc110->se_mask->HDMI_DB_DISABLE) {
		/* for bring up, disable dp double  TODO */
		if (REG(HDMI_DB_CONTROL))
			REG_UPDATE(HDMI_DB_CONTROL, HDMI_DB_DISABLE, 1);

		dce110_update_hdmi_info_packet(enc110, 0, &info_frame->avi);
		dce110_update_hdmi_info_packet(enc110, 1, &info_frame->vendor);
		dce110_update_hdmi_info_packet(enc110, 2, &info_frame->gamut);
		dce110_update_hdmi_info_packet(enc110, 3, &info_frame->spd);
		dce110_update_hdmi_info_packet(enc110, 4, &info_frame->hdrsmd);
	}
#endif
}