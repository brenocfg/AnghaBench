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
struct tc3589x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TC3589x_MANFCODE ; 
 int TC3589x_MANFCODE_MAGIC ; 
 int /*<<< orphan*/  TC3589x_RSTCTRL ; 
 int TC3589x_RSTCTRL_KBDRST ; 
 int TC3589x_RSTCTRL_ROTRST ; 
 int TC3589x_RSTCTRL_TIMRST ; 
 int /*<<< orphan*/  TC3589x_RSTINTCLR ; 
 int /*<<< orphan*/  TC3589x_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int) ; 
 int tc3589x_reg_read (struct tc3589x*,int /*<<< orphan*/ ) ; 
 int tc3589x_reg_write (struct tc3589x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc3589x_chip_init(struct tc3589x *tc3589x)
{
	int manf, ver, ret;

	manf = tc3589x_reg_read(tc3589x, TC3589x_MANFCODE);
	if (manf < 0)
		return manf;

	ver = tc3589x_reg_read(tc3589x, TC3589x_VERSION);
	if (ver < 0)
		return ver;

	if (manf != TC3589x_MANFCODE_MAGIC) {
		dev_err(tc3589x->dev, "unknown manufacturer: %#x\n", manf);
		return -EINVAL;
	}

	dev_info(tc3589x->dev, "manufacturer: %#x, version: %#x\n", manf, ver);

	/*
	 * Put everything except the IRQ module into reset;
	 * also spare the GPIO module for any pin initialization
	 * done during pre-kernel boot
	 */
	ret = tc3589x_reg_write(tc3589x, TC3589x_RSTCTRL,
				TC3589x_RSTCTRL_TIMRST
				| TC3589x_RSTCTRL_ROTRST
				| TC3589x_RSTCTRL_KBDRST);
	if (ret < 0)
		return ret;

	/* Clear the reset interrupt. */
	return tc3589x_reg_write(tc3589x, TC3589x_RSTINTCLR, 0x1);
}