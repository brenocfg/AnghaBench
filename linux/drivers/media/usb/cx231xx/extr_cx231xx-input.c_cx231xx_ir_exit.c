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
struct cx231xx {int /*<<< orphan*/ * ir_i2c_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 

void cx231xx_ir_exit(struct cx231xx *dev)
{
	if (dev->ir_i2c_client)
		i2c_unregister_device(dev->ir_i2c_client);
	dev->ir_i2c_client = NULL;
}