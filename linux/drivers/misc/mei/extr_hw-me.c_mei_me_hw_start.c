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
struct mei_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mei_me_host_set_ready (struct mei_device*) ; 
 int mei_me_hw_ready_wait (struct mei_device*) ; 

__attribute__((used)) static int mei_me_hw_start(struct mei_device *dev)
{
	int ret = mei_me_hw_ready_wait(dev);

	if (ret)
		return ret;
	dev_dbg(dev->dev, "hw is ready\n");

	mei_me_host_set_ready(dev);
	return ret;
}