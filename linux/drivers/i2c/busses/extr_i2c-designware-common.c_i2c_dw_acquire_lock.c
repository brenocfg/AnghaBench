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
struct dw_i2c_dev {int (* acquire_lock ) () ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int stub1 () ; 

int i2c_dw_acquire_lock(struct dw_i2c_dev *dev)
{
	int ret;

	if (!dev->acquire_lock)
		return 0;

	ret = dev->acquire_lock();
	if (!ret)
		return 0;

	dev_err(dev->dev, "couldn't acquire bus ownership\n");

	return ret;
}