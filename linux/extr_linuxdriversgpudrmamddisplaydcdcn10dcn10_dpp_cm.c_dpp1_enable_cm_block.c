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

/* Variables and functions */
 int /*<<< orphan*/  CM_BYPASS_EN ; 
 int /*<<< orphan*/  CM_CMOUT_CONTROL ; 
 int /*<<< orphan*/  CM_CMOUT_ROUND_TRUNC_MODE ; 
 int /*<<< orphan*/  CM_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp1_enable_cm_block(
		struct dpp *dpp_base)
{
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);

	REG_UPDATE(CM_CMOUT_CONTROL, CM_CMOUT_ROUND_TRUNC_MODE, 8);
	REG_UPDATE(CM_CONTROL, CM_BYPASS_EN, 0);
}