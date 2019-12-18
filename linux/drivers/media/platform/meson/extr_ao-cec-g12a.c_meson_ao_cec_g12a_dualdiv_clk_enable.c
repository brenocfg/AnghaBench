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
struct meson_ao_cec_g12a_dualdiv_clk {int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CECB_CLK_CNTL_BYPASS_EN ; 
 int CECB_CLK_CNTL_DUAL_EN ; 
 int CECB_CLK_CNTL_INPUT_EN ; 
 int CECB_CLK_CNTL_M1 ; 
 int CECB_CLK_CNTL_M2 ; 
 int CECB_CLK_CNTL_N1 ; 
 int CECB_CLK_CNTL_N2 ; 
 int CECB_CLK_CNTL_OUTPUT_EN ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_REG0 ; 
 int /*<<< orphan*/  CECB_CLK_CNTL_REG1 ; 
 int FIELD_PREP (int,int) ; 
 struct meson_ao_cec_g12a_dualdiv_clk* hw_to_meson_ao_cec_g12a_dualdiv_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int meson_ao_cec_g12a_dualdiv_clk_enable(struct clk_hw *hw)
{
	struct meson_ao_cec_g12a_dualdiv_clk *dualdiv_clk =
		hw_to_meson_ao_cec_g12a_dualdiv_clk(hw);


	/* Disable Input & Output */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN,
			   0);

	/* Set N1 & N2 */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_N1,
			   FIELD_PREP(CECB_CLK_CNTL_N1, 733 - 1));

	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_N2,
			   FIELD_PREP(CECB_CLK_CNTL_N2, 732 - 1));

	/* Set M1 & M2 */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_M1,
			   FIELD_PREP(CECB_CLK_CNTL_M1, 8 - 1));

	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_M2,
			   FIELD_PREP(CECB_CLK_CNTL_M2, 11 - 1));

	/* Enable Dual divisor */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_DUAL_EN, CECB_CLK_CNTL_DUAL_EN);

	/* Disable divisor bypass */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG1,
			   CECB_CLK_CNTL_BYPASS_EN, 0);

	/* Enable Input & Output */
	regmap_update_bits(dualdiv_clk->regmap, CECB_CLK_CNTL_REG0,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN,
			   CECB_CLK_CNTL_INPUT_EN | CECB_CLK_CNTL_OUTPUT_EN);

	return 0;
}