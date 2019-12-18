#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct max2165_priv {int tf_ntch_low_cfg; int tf_ntch_hi_cfg; int tf_balun_low_ref; int tf_balun_hi_ref; TYPE_1__* config; } ;
struct TYPE_2__ {int osc_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_NDIV_FRAC0 ; 
 int /*<<< orphan*/  REG_NDIV_FRAC1 ; 
 int /*<<< orphan*/  REG_NDIV_FRAC2 ; 
 int /*<<< orphan*/  REG_NDIV_INT ; 
 int /*<<< orphan*/  REG_TRACK_FILTER ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int fixpt_div32 (int,int,int*,int*) ; 
 int /*<<< orphan*/  max2165_mask_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  max2165_write_reg (struct max2165_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max2165_set_rf(struct max2165_priv *priv, u32 freq)
{
	u8 tf;
	u8 tf_ntch;
	u32 t;
	u32 quotient, fraction;
	int ret;

	/* Set PLL divider according to RF frequency */
	ret = fixpt_div32(freq / 1000, priv->config->osc_clk * 1000,
			 &quotient, &fraction);
	if (ret != 0)
		return ret;

	/* 20-bit fraction */
	fraction >>= 12;

	max2165_write_reg(priv, REG_NDIV_INT, quotient);
	max2165_mask_write_reg(priv, REG_NDIV_FRAC2, 0x0F, fraction >> 16);
	max2165_write_reg(priv, REG_NDIV_FRAC1, fraction >> 8);
	max2165_write_reg(priv, REG_NDIV_FRAC0, fraction);

	/* Norch Filter */
	tf_ntch = (freq < 725000000) ?
		priv->tf_ntch_low_cfg : priv->tf_ntch_hi_cfg;

	/* Tracking filter balun */
	t = priv->tf_balun_low_ref;
	t += (priv->tf_balun_hi_ref - priv->tf_balun_low_ref)
		* (freq / 1000 - 470000) / (780000 - 470000);

	tf = t;
	dprintk("tf = %X\n", tf);
	tf |= tf_ntch << 4;

	max2165_write_reg(priv, REG_TRACK_FILTER, tf);

	return 0;
}