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
struct dcn10_dpp {int dummy; } ;
struct dc_bias_and_scale {int /*<<< orphan*/  bias_blue; int /*<<< orphan*/  scale_blue; int /*<<< orphan*/  bias_green; int /*<<< orphan*/  scale_green; int /*<<< orphan*/  bias_red; int /*<<< orphan*/  scale_red; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BNS_BIAS_B ; 
 int /*<<< orphan*/  CM_BNS_BIAS_G ; 
 int /*<<< orphan*/  CM_BNS_BIAS_R ; 
 int /*<<< orphan*/  CM_BNS_SCALE_B ; 
 int /*<<< orphan*/  CM_BNS_SCALE_G ; 
 int /*<<< orphan*/  CM_BNS_SCALE_R ; 
 int /*<<< orphan*/  CM_BNS_VALUES_B ; 
 int /*<<< orphan*/  CM_BNS_VALUES_G ; 
 int /*<<< orphan*/  CM_BNS_VALUES_R ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

void dpp1_program_bias_and_scale(
	struct dpp *dpp_base,
	struct dc_bias_and_scale *params)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_SET_2(CM_BNS_VALUES_R, 0,
		CM_BNS_SCALE_R, params->scale_red,
		CM_BNS_BIAS_R, params->bias_red);

	REG_SET_2(CM_BNS_VALUES_G, 0,
		CM_BNS_SCALE_G, params->scale_green,
		CM_BNS_BIAS_G, params->bias_green);

	REG_SET_2(CM_BNS_VALUES_B, 0,
		CM_BNS_SCALE_B, params->scale_blue,
		CM_BNS_BIAS_B, params->bias_blue);

}