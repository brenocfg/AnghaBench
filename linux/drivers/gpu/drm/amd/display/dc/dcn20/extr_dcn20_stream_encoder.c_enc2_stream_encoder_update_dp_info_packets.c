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
typedef  scalar_t__ uint32_t ;
struct stream_encoder {int dummy; } ;
struct encoder_info_frame {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_SEC_CNTL ; 
 int /*<<< orphan*/  DP_SEC_METADATA_PACKET_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_METADATA_TRANSMISSION ; 
 int /*<<< orphan*/  DP_SEC_STREAM_ENABLE ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  enc1_stream_encoder_update_dp_info_packets (struct stream_encoder*,struct encoder_info_frame const*) ; 

__attribute__((used)) static void enc2_stream_encoder_update_dp_info_packets(
	struct stream_encoder *enc,
	const struct encoder_info_frame *info_frame)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uint32_t dmdata_packet_enabled = 0;

	enc1_stream_encoder_update_dp_info_packets(enc, info_frame);

	/* check if dynamic metadata packet transmission is enabled */
	REG_GET(DP_SEC_METADATA_TRANSMISSION,
			DP_SEC_METADATA_PACKET_ENABLE, &dmdata_packet_enabled);

	if (dmdata_packet_enabled)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
}