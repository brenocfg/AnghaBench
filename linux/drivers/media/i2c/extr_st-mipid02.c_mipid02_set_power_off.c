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
struct mipid02_dev {int /*<<< orphan*/  xclk; int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  MIPID02_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipid02_set_power_off(struct mipid02_dev *bridge)
{
	regulator_bulk_disable(MIPID02_NUM_SUPPLIES, bridge->supplies);
	clk_disable_unprepare(bridge->xclk);
}