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
struct ssp_device {int /*<<< orphan*/  clk; } ;
struct navpoint {int /*<<< orphan*/  gpio; struct ssp_device* ssp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSCR0 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void navpoint_down(struct navpoint *navpoint)
{
	struct ssp_device *ssp = navpoint->ssp;

	if (gpio_is_valid(navpoint->gpio))
		gpio_set_value(navpoint->gpio, 0);

	pxa_ssp_write_reg(ssp, SSCR0, 0);

	clk_disable_unprepare(ssp->clk);
}