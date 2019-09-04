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
struct exynos_adc {int /*<<< orphan*/  clk; int /*<<< orphan*/  sclk; TYPE_1__* data; } ;
struct TYPE_2__ {scalar_t__ needs_sclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_adc_disable_clk(struct exynos_adc *info)
{
	if (info->data->needs_sclk)
		clk_disable(info->sclk);
	clk_disable(info->clk);
}