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
struct fixed31_32 {int dummy; } ;
struct dcn10_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dcn10_stream_encoder* DCN10STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_MSE_RATE_CNTL ; 
 int /*<<< orphan*/  DP_MSE_RATE_UPDATE ; 
 int /*<<< orphan*/  DP_MSE_RATE_UPDATE_PENDING ; 
 int /*<<< orphan*/  DP_MSE_RATE_X ; 
 int /*<<< orphan*/  DP_MSE_RATE_Y ; 
 int /*<<< orphan*/  DP_MST_UPDATE_MAX_RETRY ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WAIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_ceil (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_floor (struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_shl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dc_fixpt_sub_int (struct fixed31_32,int /*<<< orphan*/ ) ; 

void enc1_stream_encoder_set_mst_bandwidth(
	struct stream_encoder *enc,
	struct fixed31_32 avg_time_slots_per_mtp)
{
	struct dcn10_stream_encoder *enc1 = DCN10STRENC_FROM_STRENC(enc);
	uint32_t x = dc_fixpt_floor(
		avg_time_slots_per_mtp);
	uint32_t y = dc_fixpt_ceil(
		dc_fixpt_shl(
			dc_fixpt_sub_int(
				avg_time_slots_per_mtp,
				x),
			26));

	REG_SET_2(DP_MSE_RATE_CNTL, 0,
		DP_MSE_RATE_X, x,
		DP_MSE_RATE_Y, y);

	/* wait for update to be completed on the link */
	/* i.e. DP_MSE_RATE_UPDATE_PENDING field (read only) */
	/* is reset to 0 (not pending) */
	REG_WAIT(DP_MSE_RATE_UPDATE, DP_MSE_RATE_UPDATE_PENDING,
			0,
			10, DP_MST_UPDATE_MAX_RETRY);
}