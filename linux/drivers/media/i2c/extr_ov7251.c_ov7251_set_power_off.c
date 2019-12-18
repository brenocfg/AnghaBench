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
struct ov7251 {int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  xclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov7251_regulators_disable (struct ov7251*) ; 

__attribute__((used)) static void ov7251_set_power_off(struct ov7251 *ov7251)
{
	clk_disable_unprepare(ov7251->xclk);
	gpiod_set_value_cansleep(ov7251->enable_gpio, 0);
	ov7251_regulators_disable(ov7251);
}