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
struct dce110_stream_encoder {int dummy; } ;

/* Variables and functions */
 struct dce110_stream_encoder* DCE110STRENC_FROM_STRENC (struct stream_encoder*) ; 
 int /*<<< orphan*/  DP_SEC_AIP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_ASP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_ATP_ENABLE ; 
 int /*<<< orphan*/  DP_SEC_CNTL ; 
 int /*<<< orphan*/  DP_SEC_STREAM_ENABLE ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dce110_se_enable_dp_audio(
	struct stream_encoder *enc)
{
	struct dce110_stream_encoder *enc110 = DCE110STRENC_FROM_STRENC(enc);

	/* Enable Audio packets */
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_ASP_ENABLE, 1);

	/* Program the ATP and AIP next */
	REG_UPDATE_2(DP_SEC_CNTL,
			DP_SEC_ATP_ENABLE, 1,
			DP_SEC_AIP_ENABLE, 1);

	/* Program STREAM_ENABLE after all the other enables. */
	REG_UPDATE(DP_SEC_CNTL, DP_SEC_STREAM_ENABLE, 1);
}