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
typedef  int u32 ;
struct ov2685 {int /*<<< orphan*/  supplies; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  xvclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2685_NUM_SUPPLIES ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int ov2685_cal_delay (int) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void __ov2685_power_off(struct ov2685 *ov2685)
{
	/* 512 xvclk cycles after the last SCCB transaction or MIPI frame end */
	u32 delay_us = ov2685_cal_delay(512);

	usleep_range(delay_us, delay_us * 2);
	clk_disable_unprepare(ov2685->xvclk);
	gpiod_set_value_cansleep(ov2685->reset_gpio, 1);
	regulator_bulk_disable(OV2685_NUM_SUPPLIES, ov2685->supplies);
}