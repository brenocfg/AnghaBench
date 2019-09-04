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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct atbm_state {TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ osc_clk_freq; scalar_t__ zif_swap_iq; } ;

/* Variables and functions */
 scalar_t__ REG_ADC_CONFIG ; 
 scalar_t__ REG_IF_FREQ ; 
 scalar_t__ REG_SWAP_I_Q ; 
 scalar_t__ REG_TUNER_BASEBAND ; 
 int /*<<< orphan*/  atbm8830_read_reg (struct atbm_state*,scalar_t__,int*) ; 
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,scalar_t__,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int set_if_freq(struct atbm_state *priv, u32 freq /*in kHz*/)
{

	u32 fs = priv->config->osc_clk_freq;
	u64 t;
	u32 val;
	u8 dat;

	if (freq != 0) {
		/* 2 * PI * (freq - fs) / fs * (2 ^ 22) */
		t = (u64) 2 * 31416 * (freq - fs);
		t <<= 22;
		do_div(t, fs);
		do_div(t, 1000);
		val = t;

		atbm8830_write_reg(priv, REG_TUNER_BASEBAND, 1);
		atbm8830_write_reg(priv, REG_IF_FREQ, val);
		atbm8830_write_reg(priv, REG_IF_FREQ+1, val >> 8);
		atbm8830_write_reg(priv, REG_IF_FREQ+2, val >> 16);

		atbm8830_read_reg(priv, REG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		atbm8830_write_reg(priv, REG_ADC_CONFIG, dat);
	} else {
		/* Zero IF */
		atbm8830_write_reg(priv, REG_TUNER_BASEBAND, 0);

		atbm8830_read_reg(priv, REG_ADC_CONFIG, &dat);
		dat &= 0xFC;
		dat |= 0x02;
		atbm8830_write_reg(priv, REG_ADC_CONFIG, dat);

		if (priv->config->zif_swap_iq)
			atbm8830_write_reg(priv, REG_SWAP_I_Q, 0x03);
		else
			atbm8830_write_reg(priv, REG_SWAP_I_Q, 0x01);
	}

	return 0;
}