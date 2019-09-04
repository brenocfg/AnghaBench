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
struct dce110_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_SEC_ACM_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_AIP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_ASP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_ATP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_CNTL ; 
 int /*<<< orphan*/  DP_SEC_STREAM_ENABLE ; 
 scalar_t__ REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dce110_se_disable_dp_audio(
	struct stream_encoder *enc)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);
	uint32_t value = 0;

	/* Disable Audio packets */
	REG_UPDATE_5(DP_SEC_CNTL,
			DP_SEC_ASP_ENABLE, 0,
			DP_SEC_ATP_ENABLE, 0,
			DP_SEC_AIP_ENABLE, 0,
			DP_SEC_ACM_ENABLE, 0,
			DP_SEC_STREAM_ENABLE, 0);

	/* This register shared with encoder info frame. Therefore we need to
	keep master enabled if at least on of the fields is not 0 */
	value = REG_READ(DP_SEC_CNTL);
	if (value != 0)
		REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);

}