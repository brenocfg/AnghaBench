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
struct clk_hw {int dummy; } ;
struct cec_32k_freq_table {int n1; int n2; int m1; int m2; scalar_t__ dualdiv; } ;
struct aoclk_cec_32k {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_CRT_CLK_CNTL1 ; 
 int /*<<< orphan*/  AO_RTC_ALT_CLK_CNTL0 ; 
 int /*<<< orphan*/  AO_RTC_ALT_CLK_CNTL1 ; 
 int /*<<< orphan*/  AO_RTI_PWR_CNTL_REG0 ; 
 int CLK_CNTL0_DUALDIV_EN ; 
 int CLK_CNTL0_IN_GATE_EN ; 
 int CLK_CNTL0_N1_MASK ; 
 int CLK_CNTL0_N2_MASK ; 
 int CLK_CNTL0_OUT_GATE_EN ; 
 int CLK_CNTL1_M1_MASK ; 
 int CLK_CNTL1_M2_MASK ; 
 int CLK_CNTL1_SELECT_OSC ; 
 int EINVAL ; 
 int FIELD_PREP (int,int) ; 
 int PWR_CNTL_ALT_32K_SEL ; 
 struct cec_32k_freq_table* find_cec_32k_freq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct aoclk_cec_32k* to_aoclk_cec_32k (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int aoclk_cec_32k_set_rate(struct clk_hw *hw, unsigned long rate,
				  unsigned long parent_rate)
{
	const struct cec_32k_freq_table *freq = find_cec_32k_freq(rate,
								  parent_rate);
	struct aoclk_cec_32k *cec_32k = to_aoclk_cec_32k(hw);
	u32 reg = 0;

	if (!freq)
		return -EINVAL;

	/* Disable clock */
	regmap_update_bits(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL0,
			   CLK_CNTL0_IN_GATE_EN | CLK_CNTL0_OUT_GATE_EN, 0);

	reg = FIELD_PREP(CLK_CNTL0_N1_MASK, freq->n1 - 1);
	if (freq->dualdiv)
		reg |= CLK_CNTL0_DUALDIV_EN |
		       FIELD_PREP(CLK_CNTL0_N2_MASK, freq->n2 - 1);

	regmap_write(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL0, reg);

	reg = FIELD_PREP(CLK_CNTL1_M1_MASK, freq->m1 - 1);
	if (freq->dualdiv)
		reg |= FIELD_PREP(CLK_CNTL1_M2_MASK, freq->m2 - 1);

	regmap_write(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL1, reg);

	/* Enable clock */
	regmap_update_bits(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL0,
			   CLK_CNTL0_IN_GATE_EN, CLK_CNTL0_IN_GATE_EN);

	udelay(200);

	regmap_update_bits(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL0,
			   CLK_CNTL0_OUT_GATE_EN, CLK_CNTL0_OUT_GATE_EN);

	regmap_update_bits(cec_32k->regmap, AO_CRT_CLK_CNTL1,
			   CLK_CNTL1_SELECT_OSC, CLK_CNTL1_SELECT_OSC);

	/* Select 32k from XTAL */
	regmap_update_bits(cec_32k->regmap,
			  AO_RTI_PWR_CNTL_REG0,
			  PWR_CNTL_ALT_32K_SEL,
			  FIELD_PREP(PWR_CNTL_ALT_32K_SEL, 4));

	return 0;
}