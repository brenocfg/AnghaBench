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
struct ov7251 {int xclk_freq; int /*<<< orphan*/  enable_gpio; int /*<<< orphan*/  dev; int /*<<< orphan*/  xclk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ov7251_regulators_disable (struct ov7251*) ; 
 int ov7251_regulators_enable (struct ov7251*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ov7251_set_power_on(struct ov7251 *ov7251)
{
	int ret;
	u32 wait_us;

	ret = ov7251_regulators_enable(ov7251);
	if (ret < 0)
		return ret;

	ret = clk_prepare_enable(ov7251->xclk);
	if (ret < 0) {
		dev_err(ov7251->dev, "clk prepare enable failed\n");
		ov7251_regulators_disable(ov7251);
		return ret;
	}

	gpiod_set_value_cansleep(ov7251->enable_gpio, 1);

	/* wait at least 65536 external clock cycles */
	wait_us = DIV_ROUND_UP(65536 * 1000,
			       DIV_ROUND_UP(ov7251->xclk_freq, 1000));
	usleep_range(wait_us, wait_us + 1000);

	return 0;
}