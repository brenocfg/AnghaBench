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
typedef  int u32 ;
struct meson_ao_cec_g12a_dualdiv_clk {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CECB_CLK_CNTL_BYPASS_EN ; 
 int CECB_CLK_CNTL_DUAL_EN ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_M1 ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_N1 ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_N2 ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_REG0 ; 
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP (int,unsigned long) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 struct meson_ao_cec_g12a_dualdiv_clk* hw_to_meson_ao_cec_g12a_dualdiv_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long
meson_ao_cec_g12a_dualdiv_clk_recalc_rate(struct clk_hw *hw,
					  unsigned long parent_rate)
{
	struct meson_ao_cec_g12a_dualdiv_clk *dualdiv_clk =
		hw_to_meson_ao_cec_g12a_dualdiv_clk(hw);
	unsigned long n1;
	u32 reg0, reg1;

	regmap_read(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0, &reg0);
	regmap_read(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0, &reg1);

	if (reg1 & CECB_CLK_CNTL_BYPASS_EN)
		return parent_rate;

	if (reg0 & CECB_CLK_CNTL_DUAL_EN) {
		unsigned long n2, m1, m2, f1, f2, p1, p2;

		n1 = FIELD_GET(CECB_CLK_CNTL_N1, reg0) + 1;
		n2 = FIELD_GET(CECB_CLK_CNTL_N2, reg0) + 1;

		m1 = FIELD_GET(CECB_CLK_CNTL_M1, reg1) + 1;
		m2 = FIELD_GET(CECB_CLK_CNTL_M1, reg1) + 1;

		f1 = DIV_ROUND_CLOSEST(parent_rate, n1);
		f2 = DIV_ROUND_CLOSEST(parent_rate, n2);

		p1 = DIV_ROUND_CLOSEST(100000000 * m1, f1 * (m1 + m2));
		p2 = DIV_ROUND_CLOSEST(100000000 * m2, f2 * (m1 + m2));

		return DIV_ROUND_UP(100000000, p1 + p2);
	}

	n1 = FIELD_GET(CECB_CLK_CNTL_N1, reg0) + 1;

	return DIV_ROUND_CLOSEST(parent_rate, n1);
}