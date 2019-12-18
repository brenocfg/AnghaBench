#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct si_power_info {scalar_t__ spll_table_start; int /*<<< orphan*/  sram_end; } ;
struct radeon_device {int dummy; } ;
struct ni_power_info {int enable_power_containment; } ;
struct TYPE_7__ {int vCG_SPLL_FUNC_CNTL; int vCG_SPLL_FUNC_CNTL_3; int vCG_SPLL_SPREAD_SPECTRUM; int vCG_SPLL_SPREAD_SPECTRUM_2; } ;
struct TYPE_6__ {void** ss; void** freq; } ;
typedef  TYPE_1__ SMC_SISLANDS_SPLL_DIV_TABLE ;
typedef  TYPE_2__ SISLANDS_SMC_SCLK_VALUE ;

/* Variables and functions */
 int CLK_S_MASK ; 
 int CLK_S_SHIFT ; 
 int CLK_V_MASK ; 
 int CLK_V_SHIFT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK ; 
 int SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT ; 
 int SPLL_FB_DIV_MASK ; 
 int SPLL_FB_DIV_SHIFT ; 
 int SPLL_PDIV_A_MASK ; 
 int SPLL_PDIV_A_SHIFT ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ni_power_info* ni_get_pi (struct radeon_device*) ; 
 int si_calculate_sclk_params (struct radeon_device*,int,TYPE_2__*) ; 
 int si_copy_bytes_to_smc (struct radeon_device*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct si_power_info* si_get_pi (struct radeon_device*) ; 

__attribute__((used)) static int si_init_smc_spll_table(struct radeon_device *rdev)
{
	struct ni_power_info *ni_pi = ni_get_pi(rdev);
	struct si_power_info *si_pi = si_get_pi(rdev);
	SMC_SISLANDS_SPLL_DIV_TABLE *spll_table;
	SISLANDS_SMC_SCLK_VALUE sclk_params;
	u32 fb_div, p_div;
	u32 clk_s, clk_v;
	u32 sclk = 0;
	int ret = 0;
	u32 tmp;
	int i;

	if (si_pi->spll_table_start == 0)
		return -EINVAL;

	spll_table = kzalloc(sizeof(SMC_SISLANDS_SPLL_DIV_TABLE), GFP_KERNEL);
	if (spll_table == NULL)
		return -ENOMEM;

	for (i = 0; i < 256; i++) {
		ret = si_calculate_sclk_params(rdev, sclk, &sclk_params);
		if (ret)
			break;

		p_div = (sclk_params.vCG_SPLL_FUNC_CNTL & SPLL_PDIV_A_MASK) >> SPLL_PDIV_A_SHIFT;
		fb_div = (sclk_params.vCG_SPLL_FUNC_CNTL_3 & SPLL_FB_DIV_MASK) >> SPLL_FB_DIV_SHIFT;
		clk_s = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM & CLK_S_MASK) >> CLK_S_SHIFT;
		clk_v = (sclk_params.vCG_SPLL_SPREAD_SPECTRUM_2 & CLK_V_MASK) >> CLK_V_SHIFT;

		fb_div &= ~0x00001FFF;
		fb_div >>= 1;
		clk_v >>= 6;

		if (p_div & ~(SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT))
			ret = -EINVAL;
		if (fb_div & ~(SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT))
			ret = -EINVAL;
		if (clk_s & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT))
			ret = -EINVAL;
		if (clk_v & ~(SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK >> SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT))
			ret = -EINVAL;

		if (ret)
			break;

		tmp = ((fb_div << SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_FBDIV_MASK) |
			((p_div << SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_PDIV_MASK);
		spll_table->freq[i] = cpu_to_be32(tmp);

		tmp = ((clk_v << SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKV_MASK) |
			((clk_s << SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_SHIFT) & SMC_SISLANDS_SPLL_DIV_TABLE_CLKS_MASK);
		spll_table->ss[i] = cpu_to_be32(tmp);

		sclk += 512;
	}


	if (!ret)
		ret = si_copy_bytes_to_smc(rdev, si_pi->spll_table_start,
					   (u8 *)spll_table, sizeof(SMC_SISLANDS_SPLL_DIV_TABLE),
					   si_pi->sram_end);

	if (ret)
		ni_pi->enable_power_containment = false;

	kfree(spll_table);

	return ret;
}