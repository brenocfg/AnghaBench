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
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_3DLUT_INDEX ; 
 int /*<<< orphan*/  CM_3DLUT_READ_WRITE_CONTROL ; 
 int /*<<< orphan*/  CM_3DLUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_select_3dlut_ram_mask(
		struct dpp *dpp_base,
		uint32_t ram_selection_mask)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_UPDATE(CM_3DLUT_READ_WRITE_CONTROL, CM_3DLUT_WRITE_EN_MASK,
			ram_selection_mask);
	REG_SET(CM_3DLUT_INDEX, 0, CM_3DLUT_INDEX, 0);
}