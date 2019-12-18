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
struct stm32_adc {scalar_t__ clk; TYPE_1__* cfg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unprepare ) (struct stm32_adc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 struct stm32_adc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct stm32_adc*) ; 

__attribute__((used)) static int stm32_adc_hw_stop(struct device *dev)
{
	struct stm32_adc *adc = dev_get_drvdata(dev);

	if (adc->cfg->unprepare)
		adc->cfg->unprepare(adc);

	if (adc->clk)
		clk_disable_unprepare(adc->clk);

	return 0;
}