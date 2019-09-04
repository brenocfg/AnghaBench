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
typedef  scalar_t__ uint32_t ;
struct stream_encoder {int dummy; } ;
struct dce110_stream_encoder {TYPE_1__* se_mask; } ;
struct TYPE_2__ {scalar_t__ DP_SEC_AVI_ENABLE; } ;

/* Variables and functions */
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_SEC_AVI_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_CNTL ; 
 int /*<<< orphan*/  DP_SEC_GSP0_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_GSP1_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_GSP2_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_GSP3_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_MPG_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_STREAM_ENABLE ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce110_stream_encoder_stop_dp_info_packets(
	struct stream_encoder *enc)
{
	/* stop generic packets on DP */
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	uint32_t value = 0;

	if (enc110->se_mask->DP_SEC_AVI_ENABLE) {
		REG_SET_7(DP_SEC_CNTL, 0,
			DP_SEC_GSP0_ENABLE, 0,
			DP_SEC_GSP1_ENABLE, 0,
			DP_SEC_GSP2_ENABLE, 0,
			DP_SEC_GSP3_ENABLE, 0,
			DP_SEC_AVI_ENABLE, 0,
			DP_SEC_MPG_ENABLE, 0,
			DP_SEC_STREAM_ENABLE, 0);
	}

	/* this register shared with audio info frame.
	 * therefore we need to keep master enabled
	 * if at least one of the fields is not 0 */
	value = REG_READ(DP_SEC_CNTL);
	if (value)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);

}