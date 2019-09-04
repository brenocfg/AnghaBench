#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct radeon_device {int dummy; } ;
struct TYPE_4__ {void* vCG_SPLL_SPREAD_SPECTRUM_2; void* vCG_SPLL_SPREAD_SPECTRUM; void* vCG_SPLL_FUNC_CNTL_4; void* vCG_SPLL_FUNC_CNTL_3; void* vCG_SPLL_FUNC_CNTL_2; void* vCG_SPLL_FUNC_CNTL; void* sclk_value; } ;
typedef  TYPE_1__ SISLANDS_SMC_SCLK_VALUE ;

/* Variables and functions */
 void* cpu_to_be32 (void*) ; 
 int si_calculate_sclk_params (struct radeon_device*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int si_populate_sclk_value(struct radeon_device *rdev,
				  u32 engine_clock,
				  SISLANDS_SMC_SCLK_VALUE *sclk)
{
	SISLANDS_SMC_SCLK_VALUE sclk_tmp;
	int ret;

	ret = si_calculate_sclk_params(rdev, engine_clock, &sclk_tmp);
	if (!ret) {
		sclk->sclk_value = cpu_to_be32(sclk_tmp.sclk_value);
		sclk->vCG_SPLL_FUNC_CNTL = cpu_to_be32(sclk_tmp.vCG_SPLL_FUNC_CNTL);
		sclk->vCG_SPLL_FUNC_CNTL_2 = cpu_to_be32(sclk_tmp.vCG_SPLL_FUNC_CNTL_2);
		sclk->vCG_SPLL_FUNC_CNTL_3 = cpu_to_be32(sclk_tmp.vCG_SPLL_FUNC_CNTL_3);
		sclk->vCG_SPLL_FUNC_CNTL_4 = cpu_to_be32(sclk_tmp.vCG_SPLL_FUNC_CNTL_4);
		sclk->vCG_SPLL_SPREAD_SPECTRUM = cpu_to_be32(sclk_tmp.vCG_SPLL_SPREAD_SPECTRUM);
		sclk->vCG_SPLL_SPREAD_SPECTRUM_2 = cpu_to_be32(sclk_tmp.vCG_SPLL_SPREAD_SPECTRUM_2);
	}

	return ret;
}