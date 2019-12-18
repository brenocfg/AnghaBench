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
struct octeon_i2c {scalar_t__ sys_freq; int /*<<< orphan*/ * clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ SYS_FREQ_DEFAULT ; 
 scalar_t__ acpi_disabled ; 
 int /*<<< orphan*/ * clk_get (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,scalar_t__*) ; 

__attribute__((used)) static void thunder_i2c_clock_enable(struct device *dev, struct octeon_i2c *i2c)
{
	int ret;

	if (acpi_disabled) {
		/* DT */
		i2c->clk = clk_get(dev, NULL);
		if (IS_ERR(i2c->clk)) {
			i2c->clk = NULL;
			goto skip;
		}

		ret = clk_prepare_enable(i2c->clk);
		if (ret)
			goto skip;
		i2c->sys_freq = clk_get_rate(i2c->clk);
	} else {
		/* ACPI */
		device_property_read_u32(dev, "sclk", &i2c->sys_freq);
	}

skip:
	if (!i2c->sys_freq)
		i2c->sys_freq = SYS_FREQ_DEFAULT;
}