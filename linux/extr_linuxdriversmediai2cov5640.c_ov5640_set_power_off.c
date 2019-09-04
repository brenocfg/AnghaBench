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
struct ov5640_dev {int /*<<< orphan*/  xclk; int /*<<< orphan*/  supplies; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV5640_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov5640_power (struct ov5640_dev*,int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ov5640_set_power_off(struct ov5640_dev *sensor)
{
	ov5640_power(sensor, false);
	regulator_bulk_disable(OV5640_NUM_SUPPLIES, sensor->supplies);
	clk_disable_unprepare(sensor->xclk);
}