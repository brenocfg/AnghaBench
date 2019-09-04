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
struct aoclk_cec_32k {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AO_RTC_ALT_CLK_CNTL0 ; 
 int /*<<< orphan*/  AO_RTC_ALT_CLK_CNTL1 ; 
 int CLK_CNTL0_DUALDIV_EN ; 
 int /*<<< orphan*/  CLK_CNTL0_N1_MASK ; 
 int /*<<< orphan*/  CLK_CNTL0_N2_MASK ; 
 int CLK_CNTL1_BYPASS_EN ; 
 int /*<<< orphan*/  CLK_CNTL1_M1_MASK ; 
 int /*<<< orphan*/  CLK_CNTL1_M2_MASK ; 
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long DIV_ROUND_UP (int,unsigned long) ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct aoclk_cec_32k* to_aoclk_cec_32k (struct clk_hw*) ; 

__attribute__((used)) static unsigned long aoclk_cec_32k_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct aoclk_cec_32k *cec_32k = to_aoclk_cec_32k(hw);
	unsigned long n1;
	u32 reg0, reg1;

	regmap_read(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL0, &reg0);
	regmap_read(cec_32k->regmap, AO_RTC_ALT_CLK_CNTL1, &reg1);

	if (reg1 & CLK_CNTL1_BYPASS_EN)
		return parent_rate;

	if (reg0 & CLK_CNTL0_DUALDIV_EN) {
		unsigned long n2, m1, m2, f1, f2, p1, p2;

		n1 = FIELD_GET(CLK_CNTL0_N1_MASK, reg0) + 1;
		n2 = FIELD_GET(CLK_CNTL0_N2_MASK, reg0) + 1;

		m1 = FIELD_GET(CLK_CNTL1_M1_MASK, reg1) + 1;
		m2 = FIELD_GET(CLK_CNTL1_M2_MASK, reg1) + 1;

		f1 = DIV_ROUND_CLOSEST(parent_rate, n1);
		f2 = DIV_ROUND_CLOSEST(parent_rate, n2);

		p1 = DIV_ROUND_CLOSEST(100000000 * m1, f1 * (m1 + m2));
		p2 = DIV_ROUND_CLOSEST(100000000 * m2, f2 * (m1 + m2));

		return DIV_ROUND_UP(100000000, p1 + p2);
	}

	n1 = FIELD_GET(CLK_CNTL0_N1_MASK, reg0) + 1;

	return DIV_ROUND_CLOSEST(parent_rate, n1);
}