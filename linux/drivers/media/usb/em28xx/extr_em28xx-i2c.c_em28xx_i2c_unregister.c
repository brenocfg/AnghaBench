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
struct em28xx {int /*<<< orphan*/ * i2c_adap; } ;

/* Variables and functions */
 int ENODEV ; 
 unsigned int NUM_I2C_BUSES ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

int em28xx_i2c_unregister(struct em28xx *dev, unsigned int bus)
{
	if (bus >= NUM_I2C_BUSES)
		return -ENODEV;

	i2c_del_adapter(&dev->i2c_adap[bus]);
	return 0;
}