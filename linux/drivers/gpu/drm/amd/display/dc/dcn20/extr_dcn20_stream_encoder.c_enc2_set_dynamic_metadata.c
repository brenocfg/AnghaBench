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
typedef  int /*<<< orphan*/  uint32_t ;
struct stream_encoder {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;
typedef  enum dynamic_metadata_mode { ____Placeholder_dynamic_metadata_mode } dynamic_metadata_mode ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DIG_FE_CNTL ; 
 int /*<<< orphan*/  DME_CONTROL ; 
 int /*<<< orphan*/  DOLBY_VISION_EN ; 
 int /*<<< orphan*/  DP_SEC_METADATA_PACKET_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_METADATA_PACKET_LINE ; 
 int /*<<< orphan*/  DP_SEC_METADATA_PACKET_LINE_REFERENCE ; 
 int /*<<< orphan*/  DP_SEC_METADATA_TRANSMISSION ; 
 int /*<<< orphan*/  HDMI_METADATA_PACKET_CONTROL ; 
 int /*<<< orphan*/  HDMI_METADATA_PACKET_ENABLE ; 
 int /*<<< orphan*/  HDMI_METADATA_PACKET_LINE ; 
 int /*<<< orphan*/  HDMI_METADATA_PACKET_LINE_REFERENCE ; 
 int /*<<< orphan*/  METADATA_ENGINE_EN ; 
 int /*<<< orphan*/  METADATA_HUBP_REQUESTOR_ID ; 
 int /*<<< orphan*/  METADATA_STREAM_TYPE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int dmdata_dolby_vision ; 
 int dmdata_dp ; 

void enc2_set_dynamic_metadata(struct stream_encoder *enc,
		bool enable_dme,
		uint32_t hubp_requestor_id,
		enum dynamic_metadata_mode dmdata_mode)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);

	if (enable_dme) {
		REG_UPDATE_2(DME_CONTROL,
				METADATA_HUBP_REQUESTOR_ID, hubp_requestor_id,
				METADATA_STREAM_TYPE, (dmdata_mode == dmdata_dolby_vision) ? 1 : 0);

		/* Use default line reference DP_SOF for bringup.
		 * Should use OTG_SOF for DRR cases
		 */
		if (dmdata_mode == dmdata_dp)
			REG_UPDATE_3(DP_SEC_METADATA_TRANSMISSION,
					DP_SEC_METADATA_PACKET_ENABLE, 1,
					DP_SEC_METADATA_PACKET_LINE_REFERENCE, 0,
					DP_SEC_METADATA_PACKET_LINE, 20);
		else {
			REG_UPDATE_3(HDMI_METADATA_PACKET_CONTROL,
					HDMI_METADATA_PACKET_ENABLE, 1,
					HDMI_METADATA_PACKET_LINE_REFERENCE, 0,
					HDMI_METADATA_PACKET_LINE, 2);

			if (dmdata_mode == dmdata_dolby_vision)
				REG_UPDATE(DIG_FE_CNTL,
						DOLBY_VISION_EN, 1);
		}

		REG_UPDATE(DME_CONTROL,
				METADATA_ENGINE_EN, 1);
	} else {
		REG_UPDATE(DME_CONTROL,
				METADATA_ENGINE_EN, 0);

		if (dmdata_mode == dmdata_dp)
			REG_UPDATE(DP_SEC_METADATA_TRANSMISSION,
					DP_SEC_METADATA_PACKET_ENABLE, 0);
		else {
			REG_UPDATE(HDMI_METADATA_PACKET_CONTROL,
					HDMI_METADATA_PACKET_ENABLE, 0);
			REG_UPDATE(DIG_FE_CNTL,
					DOLBY_VISION_EN, 0);
		}
	}
}