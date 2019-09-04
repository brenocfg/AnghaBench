#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpga_manager {int dummy; } ;
struct device {TYPE_2__* parent; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct fpga_manager* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct fpga_manager* to_fpga_manager (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct fpga_manager *__fpga_mgr_get(struct device *dev)
{
	struct fpga_manager *mgr;

	mgr = to_fpga_manager(dev);

	if (!try_module_get(dev->parent->driver->owner))
		goto err_dev;

	return mgr;

err_dev:
	put_device(dev);
	return ERR_PTR(-ENODEV);
}