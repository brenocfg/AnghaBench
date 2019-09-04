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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ base; } ;
struct geni_i2c_dev {TYPE_1__ se; struct geni_i2c_clk_fld* clk_fld; } ;
struct geni_i2c_clk_fld {int clk_div; int t_high_cnt; int t_low_cnt; int t_cycle_cnt; } ;

/* Variables and functions */
 int CLK_DIV_SHFT ; 
 scalar_t__ GENI_SER_M_CLK_CFG ; 
 int HIGH_COUNTER_SHFT ; 
 int LOW_COUNTER_SHFT ; 
 int SER_CLK_EN ; 
 scalar_t__ SE_GENI_CLK_SEL ; 
 scalar_t__ SE_I2C_SCL_COUNTERS ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void qcom_geni_i2c_conf(struct geni_i2c_dev *gi2c)
{
	const struct geni_i2c_clk_fld *itr = gi2c->clk_fld;
	u32 val;

	writel_relaxed(0, gi2c->se.base + SE_GENI_CLK_SEL);

	val = (itr->clk_div << CLK_DIV_SHFT) | SER_CLK_EN;
	writel_relaxed(val, gi2c->se.base + GENI_SER_M_CLK_CFG);

	val = itr->t_high_cnt << HIGH_COUNTER_SHFT;
	val |= itr->t_low_cnt << LOW_COUNTER_SHFT;
	val |= itr->t_cycle_cnt;
	writel_relaxed(val, gi2c->se.base + SE_I2C_SCL_COUNTERS);
}