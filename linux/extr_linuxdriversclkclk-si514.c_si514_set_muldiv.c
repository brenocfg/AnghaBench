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
typedef  int u8 ;
struct clk_si514_muldiv {int m_int; int m_frac; int hs_div; int ls_div_bits; } ;
struct clk_si514 {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  SI514_REG_HS_DIV ; 
 int /*<<< orphan*/  SI514_REG_LP ; 
 int /*<<< orphan*/  SI514_REG_M_FRAC1 ; 
 int regmap_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si514_set_muldiv(struct clk_si514 *data,
	struct clk_si514_muldiv *settings)
{
	u8 lp;
	u8 reg[7];
	int err;

	/* Calculate LP1/LP2 according to table 13 in the datasheet */
	/* 65.259980246 */
	if (settings->m_int < 65 ||
		(settings->m_int == 65 && settings->m_frac <= 139575831))
		lp = 0x22;
	/* 67.859763463 */
	else if (settings->m_int < 67 ||
		(settings->m_int == 67 && settings->m_frac <= 461581994))
		lp = 0x23;
	/* 72.937624981 */
	else if (settings->m_int < 72 ||
		(settings->m_int == 72 && settings->m_frac <= 503383578))
		lp = 0x33;
	/* 75.843265046 */
	else if (settings->m_int < 75 ||
		(settings->m_int == 75 && settings->m_frac <= 452724474))
		lp = 0x34;
	else
		lp = 0x44;

	err = regmap_write(data->regmap, SI514_REG_LP, lp);
	if (err < 0)
		return err;

	reg[0] = settings->m_frac;
	reg[1] = settings->m_frac >> 8;
	reg[2] = settings->m_frac >> 16;
	reg[3] = settings->m_frac >> 24 | settings->m_int << 5;
	reg[4] = settings->m_int >> 3;
	reg[5] = settings->hs_div;
	reg[6] = (settings->hs_div >> 8) | (settings->ls_div_bits << 4);

	err = regmap_bulk_write(data->regmap, SI514_REG_HS_DIV, reg + 5, 2);
	if (err < 0)
		return err;
	/*
	 * Writing to SI514_REG_M_INT_FRAC triggers the clock change, so that
	 * must be written last
	 */
	return regmap_bulk_write(data->regmap, SI514_REG_M_FRAC1, reg, 5);
}