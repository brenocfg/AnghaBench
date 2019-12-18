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
typedef  int u64 ;
typedef  int u32 ;
struct atbm_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_OSC_CLK ; 
 int /*<<< orphan*/  atbm8830_write_reg (struct atbm_state*,scalar_t__,int) ; 
 int /*<<< orphan*/  do_div (int,int) ; 

__attribute__((used)) static int set_osc_freq(struct atbm_state *priv, u32 freq /*in kHz*/)
{
	u32 val;
	u64 t;

	/* 0x100000 * freq / 30.4MHz */
	t = (u64)0x100000 * freq;
	do_div(t, 30400);
	val = t;

	atbm8830_write_reg(priv, REG_OSC_CLK, val);
	atbm8830_write_reg(priv, REG_OSC_CLK + 1, val >> 8);
	atbm8830_write_reg(priv, REG_OSC_CLK + 2, val >> 16);

	return 0;
}