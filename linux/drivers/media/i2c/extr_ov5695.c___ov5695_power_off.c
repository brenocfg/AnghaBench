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
struct ov5695 {int /*<<< orphan*/  supplies; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  xvclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5695_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ov5695_power_off(struct ov5695 *ov5695)
{
	clk_disable_unprepare(ov5695->xvclk);
	gpiod_set_value_cansleep(ov5695->reset_gpio, 1);
	regulator_bulk_disable(OV5695_NUM_SUPPLIES, ov5695->supplies);
}