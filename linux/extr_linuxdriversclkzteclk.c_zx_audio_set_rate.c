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
typedef  int /*<<< orphan*/  u32 ;
struct clk_zx_audio {int /*<<< orphan*/  reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  calc_reg (unsigned long,unsigned long) ; 
 struct clk_zx_audio* to_clk_zx_audio (struct clk_hw*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zx_audio_set_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long parent_rate)
{
	struct clk_zx_audio *zx_audio = to_clk_zx_audio(hw);
	u32 reg;

	reg = calc_reg(parent_rate, rate);
	writel_relaxed(reg, zx_audio->reg_base);

	return 0;
}