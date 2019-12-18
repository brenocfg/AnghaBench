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
struct saa7134_dev {int dummy; } ;
typedef  enum i2c_status { ____Placeholder_i2c_status } i2c_status ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_WAIT_DELAY ; 
 int I2C_WAIT_RETRY ; 
 int i2c_get_status (struct saa7134_dev*) ; 
 int /*<<< orphan*/  i2c_is_busy (int) ; 
 int /*<<< orphan*/  saa_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_is_busy_wait(struct saa7134_dev *dev)
{
	enum i2c_status status;
	int count;

	for (count = 0; count < I2C_WAIT_RETRY; count++) {
		status = i2c_get_status(dev);
		if (!i2c_is_busy(status))
			break;
		saa_wait(I2C_WAIT_DELAY);
	}
	if (I2C_WAIT_RETRY == count)
		return false;
	return true;
}