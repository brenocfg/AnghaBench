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
 int /*<<< orphan*/  MMA8450_CTRL_REG2 ; 
 int /*<<< orphan*/  mma8450_write (struct mma8450*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mma8450_close(struct input_polled_dev *dev)
{
	struct mma8450 *m = dev->private;

	mma8450_write(m, MMA8450_CTRL_REG1, 0x00);
	mma8450_write(m, MMA8450_CTRL_REG2, 0x01);
}