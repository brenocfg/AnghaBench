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
struct lis3lv02d {int /*<<< orphan*/  regulators; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int LIS3_REG_OFF ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lis3_reg_ctrl(struct lis3lv02d *lis3, bool state)
{
	int ret;
	if (state == LIS3_REG_OFF) {
		ret = regulator_bulk_disable(ARRAY_SIZE(lis3->regulators),
					lis3->regulators);
	} else {
		ret = regulator_bulk_enable(ARRAY_SIZE(lis3->regulators),
					lis3->regulators);
		/* Chip needs time to wakeup. Not mentioned in datasheet */
		usleep_range(10000, 20000);
	}
	return ret;
}