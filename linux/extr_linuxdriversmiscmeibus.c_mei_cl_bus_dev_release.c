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
struct mei_cl_device {struct mei_cl_device* cl; int /*<<< orphan*/  bus; int /*<<< orphan*/  me_cl; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_cl_unlink (struct mei_cl_device*) ; 
 int /*<<< orphan*/  mei_dev_bus_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_put (int /*<<< orphan*/ ) ; 
 struct mei_cl_device* to_mei_cl_device (struct device*) ; 

__attribute__((used)) static void mei_cl_bus_dev_release(struct device *dev)
{
	struct mei_cl_device *cldev = to_mei_cl_device(dev);

	if (!cldev)
		return;

	mei_me_cl_put(cldev->me_cl);
	mei_dev_bus_put(cldev->bus);
	mei_cl_unlink(cldev->cl);
	kfree(cldev->cl);
	kfree(cldev);
}