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
struct sh_mobile_i2c_data {int clks_per_count; scalar_t__ bus_speed; int /*<<< orphan*/  icch; int /*<<< orphan*/  iccl; int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FAST_MODE ; 
 scalar_t__ STANDARD_MODE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int sh_mobile_i2c_check_timing (struct sh_mobile_i2c_data*) ; 
 int /*<<< orphan*/  sh_mobile_i2c_icch (unsigned long,int,int) ; 
 int /*<<< orphan*/  sh_mobile_i2c_iccl (unsigned long,int,int) ; 

__attribute__((used)) static int sh_mobile_i2c_init(struct sh_mobile_i2c_data *pd)
{
	unsigned long i2c_clk_khz;
	u32 tHIGH, tLOW, tf;

	i2c_clk_khz = clk_get_rate(pd->clk) / 1000 / pd->clks_per_count;

	if (pd->bus_speed == STANDARD_MODE) {
		tLOW	= 47;	/* tLOW = 4.7 us */
		tHIGH	= 40;	/* tHD;STA = tHIGH = 4.0 us */
		tf	= 3;	/* tf = 0.3 us */
	} else if (pd->bus_speed == FAST_MODE) {
		tLOW	= 13;	/* tLOW = 1.3 us */
		tHIGH	= 6;	/* tHD;STA = tHIGH = 0.6 us */
		tf	= 3;	/* tf = 0.3 us */
	} else {
		dev_err(pd->dev, "unrecognized bus speed %lu Hz\n",
			pd->bus_speed);
		return -EINVAL;
	}

	pd->iccl = sh_mobile_i2c_iccl(i2c_clk_khz, tLOW, tf);
	pd->icch = sh_mobile_i2c_icch(i2c_clk_khz, tHIGH, tf);

	return sh_mobile_i2c_check_timing(pd);
}