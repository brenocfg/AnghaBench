#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dpp {TYPE_3__* ctx; } ;
struct dcn20_dpp {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {scalar_t__ cm_in_bypass; } ;
struct TYPE_5__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_BYPASS ; 
 int /*<<< orphan*/  CM_CONTROL ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp2_enable_cm_block(
		struct dpp *dpp_base)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	unsigned int cm_bypass_mode = 0;
	//Temp, put CM in bypass mode
	if (dpp_base->ctx->dc->debug.cm_in_bypass)
		cm_bypass_mode = 1;

	REG_UPDATE(CM_CONTROL, CM_BYPASS, cm_bypass_mode);
}