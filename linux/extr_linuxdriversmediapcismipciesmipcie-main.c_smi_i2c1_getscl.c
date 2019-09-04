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
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_B_SW_CTL ; 
 int smi_i2c_getscl (struct smi_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smi_i2c1_getscl(void *data)
{
	struct smi_dev *dev = data;

	return	smi_i2c_getscl(dev, I2C_B_SW_CTL);
}