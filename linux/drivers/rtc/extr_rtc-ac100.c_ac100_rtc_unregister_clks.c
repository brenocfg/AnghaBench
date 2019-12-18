#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ac100_rtc_dev {TYPE_2__* rtc_32k_clk; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister_fixed_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ac100_rtc_unregister_clks(struct ac100_rtc_dev *chip)
{
	of_clk_del_provider(chip->dev->of_node);
	clk_unregister_fixed_rate(chip->rtc_32k_clk->clk);
}