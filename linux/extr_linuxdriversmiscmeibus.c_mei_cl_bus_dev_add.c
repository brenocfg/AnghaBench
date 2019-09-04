#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mei_cl_device {int is_added; int /*<<< orphan*/  dev; int /*<<< orphan*/  me_cl; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mei_me_cl_uuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_me_cl_ver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mei_cl_bus_dev_add(struct mei_cl_device *cldev)
{
	int ret;

	dev_dbg(cldev->bus->dev, "adding %pUL:%02X\n",
		mei_me_cl_uuid(cldev->me_cl),
		mei_me_cl_ver(cldev->me_cl));
	ret = device_add(&cldev->dev);
	if (!ret)
		cldev->is_added = 1;

	return ret;
}