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
struct mma8450 {int dummy; } ;
struct input_polled_dev {struct mma8450* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMA8450_CTRL_REG1 ; 
 int /*<<< orphan*/  MMA8450_XYZ_DATA_CFG ; 
 int /*<<< orphan*/  MODE_CHANGE_DELAY_MS ; 
 int mma8450_write (struct mma8450*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mma8450_open(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;
	int err;

	/* enable all events from X/Y/Z, no FIFO */
	err = mma8450_write(m, MMA8450_XYZ_DATA_CFG, 0x07);
	if (err)
		return;

	/*
	 * Sleep mode poll rate - 50Hz
	 * System output data rate - 400Hz
	 * Full scale selection - Active, +/- 2G
	 */
	err = mma8450_write(m, MMA8450_CTRL_REG1, 0x01);
	if (err < 0)
		return;

	msleep(MODE_CHANGE_DELAY_MS);
}