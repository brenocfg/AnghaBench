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
struct bcm_kona_i2c_dev {scalar_t__ base; TYPE_1__* std_cfg; } ;
struct TYPE_2__ {int prescale; int time_p; int no_div; int time_div; int time_m; int time_n; } ;

/* Variables and functions */
 int CLKEN_CLKEN_MASK ; 
 int CLKEN_M_SHIFT ; 
 int CLKEN_N_SHIFT ; 
 scalar_t__ CLKEN_OFFSET ; 
 int HSTIM_HS_MODE_MASK ; 
 scalar_t__ HSTIM_OFFSET ; 
 int TIM_DIV_SHIFT ; 
 int TIM_NO_DIV_SHIFT ; 
 scalar_t__ TIM_OFFSET ; 
 int TIM_PRESCALE_SHIFT ; 
 int TIM_P_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm_kona_i2c_config_timing(struct bcm_kona_i2c_dev *dev)
{
	writel(readl(dev->base + HSTIM_OFFSET) & ~HSTIM_HS_MODE_MASK,
	       dev->base + HSTIM_OFFSET);

	writel((dev->std_cfg->prescale << TIM_PRESCALE_SHIFT) |
	       (dev->std_cfg->time_p << TIM_P_SHIFT) |
	       (dev->std_cfg->no_div << TIM_NO_DIV_SHIFT) |
	       (dev->std_cfg->time_div	<< TIM_DIV_SHIFT),
	       dev->base + TIM_OFFSET);

	writel((dev->std_cfg->time_m << CLKEN_M_SHIFT) |
	       (dev->std_cfg->time_n << CLKEN_N_SHIFT) |
	       CLKEN_CLKEN_MASK,
	       dev->base + CLKEN_OFFSET);
}