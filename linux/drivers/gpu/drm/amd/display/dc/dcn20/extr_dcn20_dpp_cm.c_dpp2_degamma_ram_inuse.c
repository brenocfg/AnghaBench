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
typedef  int uint32_t ;
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_DGAM_CONFIG_STATUS ; 
 int /*<<< orphan*/  CM_DGAM_LUT_WRITE_EN_MASK ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static bool dpp2_degamma_ram_inuse(
		struct dpp *dpp_base,
		bool *ram_a_inuse)
{
	bool ret = false;
	uint32_t status_reg = 0;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_GET(CM_DGAM_LUT_WRITE_EN_MASK, CM_DGAM_CONFIG_STATUS,
			&status_reg);

	if (status_reg == 3) {
		*ram_a_inuse = true;
		ret = true;
	} else if (status_reg == 4) {
		*ram_a_inuse = false;
		ret = true;
	}
	return ret;
}