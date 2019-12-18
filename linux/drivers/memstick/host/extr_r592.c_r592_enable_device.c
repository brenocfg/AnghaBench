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
struct r592_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R592_IO ; 
 int /*<<< orphan*/  R592_IO_RESET ; 
 int /*<<< orphan*/  R592_POWER ; 
 int R592_POWER_0 ; 
 int R592_POWER_1 ; 
 int /*<<< orphan*/  dbg (char*,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  r592_set_reg_mask (struct r592_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r592_write_reg (struct r592_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int r592_enable_device(struct r592_device *dev, bool enable)
{
	dbg("%sabling the device", enable ? "en" : "dis");

	if (enable) {

		/* Power up the card */
		r592_write_reg(dev, R592_POWER, R592_POWER_0 | R592_POWER_1);

		/* Perform a reset */
		r592_set_reg_mask(dev, R592_IO, R592_IO_RESET);

		msleep(100);
	} else
		/* Power down the card */
		r592_write_reg(dev, R592_POWER, 0);

	return 0;
}