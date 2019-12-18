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
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
struct dc_bias_and_scale {int /*<<< orphan*/  scale_blue; int /*<<< orphan*/  scale_green; int /*<<< orphan*/  scale_red; int /*<<< orphan*/  bias_blue; int /*<<< orphan*/  bias_green; int /*<<< orphan*/  bias_red; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCNV_FP_BIAS_B ; 
 int /*<<< orphan*/  FCNV_FP_BIAS_G ; 
 int /*<<< orphan*/  FCNV_FP_BIAS_R ; 
 int /*<<< orphan*/  FCNV_FP_SCALE_B ; 
 int /*<<< orphan*/  FCNV_FP_SCALE_G ; 
 int /*<<< orphan*/  FCNV_FP_SCALE_R ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

void dpp2_cnv_set_bias_scale(
		struct dpp *dpp_base,
		struct  dc_bias_and_scale *bias_and_scale)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(FCNV_FP_BIAS_R, FCNV_FP_BIAS_R, bias_and_scale->bias_red);
	REG_UPDATE(FCNV_FP_BIAS_G, FCNV_FP_BIAS_G, bias_and_scale->bias_green);
	REG_UPDATE(FCNV_FP_BIAS_B, FCNV_FP_BIAS_B, bias_and_scale->bias_blue);
	REG_UPDATE(FCNV_FP_SCALE_R, FCNV_FP_SCALE_R, bias_and_scale->scale_red);
	REG_UPDATE(FCNV_FP_SCALE_G, FCNV_FP_SCALE_G, bias_and_scale->scale_green);
	REG_UPDATE(FCNV_FP_SCALE_B, FCNV_FP_SCALE_B, bias_and_scale->scale_blue);
}