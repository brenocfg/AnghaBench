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
struct iio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD5755_WRITE_REG_CTRL (unsigned int) ; 
 int ad5755_write_unlocked (struct iio_dev*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ad5755_write_ctrl_unlocked(struct iio_dev *indio_dev,
	unsigned int channel, unsigned int reg, unsigned int val)
{
	return ad5755_write_unlocked(indio_dev,
		AD5755_WRITE_REG_CTRL(channel), (reg << 13) | val);
}