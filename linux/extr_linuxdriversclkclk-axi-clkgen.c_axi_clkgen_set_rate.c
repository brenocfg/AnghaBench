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
struct clk_hw {int dummy; } ;
struct axi_clkgen {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MMCM_REG_CLKOUT0_1 ; 
 int /*<<< orphan*/  MMCM_REG_CLKOUT0_2 ; 
 int /*<<< orphan*/  MMCM_REG_CLK_DIV ; 
 int /*<<< orphan*/  MMCM_REG_CLK_FB1 ; 
 int /*<<< orphan*/  MMCM_REG_CLK_FB2 ; 
 int /*<<< orphan*/  MMCM_REG_FILTER1 ; 
 int /*<<< orphan*/  MMCM_REG_FILTER2 ; 
 int /*<<< orphan*/  MMCM_REG_LOCK1 ; 
 int /*<<< orphan*/  MMCM_REG_LOCK2 ; 
 int /*<<< orphan*/  MMCM_REG_LOCK3 ; 
 int /*<<< orphan*/  axi_clkgen_calc_clk_params (unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  axi_clkgen_calc_params (unsigned long,unsigned long,unsigned int*,unsigned int*,unsigned int*) ; 
 int axi_clkgen_lookup_filter (unsigned int) ; 
 int axi_clkgen_lookup_lock (unsigned int) ; 
 int /*<<< orphan*/  axi_clkgen_mmcm_write (struct axi_clkgen*,int /*<<< orphan*/ ,int,int) ; 
 struct axi_clkgen* clk_hw_to_axi_clkgen (struct clk_hw*) ; 

__attribute__((used)) static int axi_clkgen_set_rate(struct clk_hw *clk_hw,
	unsigned long rate, unsigned long parent_rate)
{
	struct axi_clkgen *axi_clkgen = clk_hw_to_axi_clkgen(clk_hw);
	unsigned int d, m, dout;
	unsigned int nocount;
	unsigned int high;
	unsigned int edge;
	unsigned int low;
	uint32_t filter;
	uint32_t lock;

	if (parent_rate == 0 || rate == 0)
		return -EINVAL;

	axi_clkgen_calc_params(parent_rate, rate, &d, &m, &dout);

	if (d == 0 || dout == 0 || m == 0)
		return -EINVAL;

	filter = axi_clkgen_lookup_filter(m - 1);
	lock = axi_clkgen_lookup_lock(m - 1);

	axi_clkgen_calc_clk_params(dout, &low, &high, &edge, &nocount);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_CLKOUT0_1,
		(high << 6) | low, 0xefff);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_CLKOUT0_2,
		(edge << 7) | (nocount << 6), 0x03ff);

	axi_clkgen_calc_clk_params(d, &low, &high, &edge, &nocount);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_CLK_DIV,
		(edge << 13) | (nocount << 12) | (high << 6) | low, 0x3fff);

	axi_clkgen_calc_clk_params(m, &low, &high, &edge, &nocount);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_CLK_FB1,
		(high << 6) | low, 0xefff);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_CLK_FB2,
		(edge << 7) | (nocount << 6), 0x03ff);

	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_LOCK1, lock & 0x3ff, 0x3ff);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_LOCK2,
		(((lock >> 16) & 0x1f) << 10) | 0x1, 0x7fff);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_LOCK3,
		(((lock >> 24) & 0x1f) << 10) | 0x3e9, 0x7fff);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_FILTER1, filter >> 16, 0x9900);
	axi_clkgen_mmcm_write(axi_clkgen, MMCM_REG_FILTER2, filter, 0x9900);

	return 0;
}