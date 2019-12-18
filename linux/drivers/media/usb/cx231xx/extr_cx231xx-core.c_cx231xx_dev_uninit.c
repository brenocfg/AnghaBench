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
struct cx231xx {int /*<<< orphan*/ * i2c_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx231xx_i2c_mux_unregister (struct cx231xx*) ; 
 int /*<<< orphan*/  cx231xx_i2c_unregister (int /*<<< orphan*/ *) ; 

void cx231xx_dev_uninit(struct cx231xx *dev)
{
	/* Un Initialize I2C bus */
	cx231xx_i2c_mux_unregister(dev);
	cx231xx_i2c_unregister(&dev->i2c_bus[2]);
	cx231xx_i2c_unregister(&dev->i2c_bus[1]);
	cx231xx_i2c_unregister(&dev->i2c_bus[0]);
}