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
typedef  int u8 ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MASK_PALEVEL_OUTPUT_POWER ; 
 int MASK_PALEVEL_PA0 ; 
 int MASK_PALEVEL_PA1 ; 
 int MASK_PALEVEL_PA2 ; 
 int /*<<< orphan*/  REG_OCP ; 
 int /*<<< orphan*/  REG_PALEVEL ; 
 int /*<<< orphan*/  REG_TESTPA1 ; 
 int /*<<< orphan*/  REG_TESTPA2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int rf69_read_mod_write (struct spi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rf69_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 

int rf69_set_output_power_level(struct spi_device *spi, u8 power_level)
{
	u8 pa_level, ocp, test_pa1, test_pa2;
	bool pa0, pa1, pa2, high_power;
	u8 min_power_level;

	// check register pa_level
	pa_level = rf69_read_reg(spi, REG_PALEVEL);
	pa0 = pa_level & MASK_PALEVEL_PA0;
	pa1 = pa_level & MASK_PALEVEL_PA1;
	pa2 = pa_level & MASK_PALEVEL_PA2;

	// check high power mode
	ocp = rf69_read_reg(spi, REG_OCP);
	test_pa1 = rf69_read_reg(spi, REG_TESTPA1);
	test_pa2 = rf69_read_reg(spi, REG_TESTPA2);
	high_power = (ocp == 0x0f) && (test_pa1 == 0x5d) && (test_pa2 == 0x7c);

	if (pa0 && !pa1 && !pa2) {
		power_level += 18;
		min_power_level = 0;
	} else if (!pa0 && pa1 && !pa2) {
		power_level += 18;
		min_power_level = 16;
	} else if (!pa0 && pa1 && pa2) {
		if (high_power)
			power_level += 11;
		else
			power_level += 14;
		min_power_level = 16;
	} else {
		goto failed;
	}

	// check input value
	if (power_level > 0x1f)
		goto failed;

	if (power_level < min_power_level)
		goto failed;

	// write value
	return rf69_read_mod_write(spi, REG_PALEVEL, MASK_PALEVEL_OUTPUT_POWER,
				   power_level);
failed:
	dev_dbg(&spi->dev, "set: illegal input param");
	return -EINVAL;
}