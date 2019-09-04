#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ smiapp_profile; } ;
struct TYPE_6__ {int /*<<< orphan*/  sys_clk_div; int /*<<< orphan*/  pix_clk_div; int /*<<< orphan*/  sys_clk_freq_hz; } ;
struct TYPE_4__ {int /*<<< orphan*/  sys_clk_div; int /*<<< orphan*/  pix_clk_div; } ;
struct smiapp_pll {TYPE_3__ op; int /*<<< orphan*/  pll_multiplier; int /*<<< orphan*/  pre_pll_clk_div; TYPE_1__ vt; } ;
struct smiapp_sensor {TYPE_2__ minfo; struct smiapp_pll pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SMIAPP_PROFILE_0 ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_OP_PIX_CLK_DIV ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_OP_SYS_CLK_DIV ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_PLL_MULTIPLIER ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_PRE_PLL_CLK_DIV ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_VT_PIX_CLK_DIV ; 
 int /*<<< orphan*/  SMIAPP_REG_U16_VT_SYS_CLK_DIV ; 
 int /*<<< orphan*/  SMIAPP_REG_U32_REQUESTED_LINK_BIT_RATE_MBPS ; 
 int smiapp_write (struct smiapp_sensor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smiapp_pll_configure(struct smiapp_sensor *sensor)
{
	struct smiapp_pll *pll = &sensor->pll;
	int rval;

	rval = smiapp_write(
		sensor, SMIAPP_REG_U16_VT_PIX_CLK_DIV, pll->vt.pix_clk_div);
	if (rval < 0)
		return rval;

	rval = smiapp_write(
		sensor, SMIAPP_REG_U16_VT_SYS_CLK_DIV, pll->vt.sys_clk_div);
	if (rval < 0)
		return rval;

	rval = smiapp_write(
		sensor, SMIAPP_REG_U16_PRE_PLL_CLK_DIV, pll->pre_pll_clk_div);
	if (rval < 0)
		return rval;

	rval = smiapp_write(
		sensor, SMIAPP_REG_U16_PLL_MULTIPLIER, pll->pll_multiplier);
	if (rval < 0)
		return rval;

	/* Lane op clock ratio does not apply here. */
	rval = smiapp_write(
		sensor, SMIAPP_REG_U32_REQUESTED_LINK_BIT_RATE_MBPS,
		DIV_ROUND_UP(pll->op.sys_clk_freq_hz, 1000000 / 256 / 256));
	if (rval < 0 || sensor->minfo.smiapp_profile == SMIAPP_PROFILE_0)
		return rval;

	rval = smiapp_write(
		sensor, SMIAPP_REG_U16_OP_PIX_CLK_DIV, pll->op.pix_clk_div);
	if (rval < 0)
		return rval;

	return smiapp_write(
		sensor, SMIAPP_REG_U16_OP_SYS_CLK_DIV, pll->op.sys_clk_div);
}