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
struct TYPE_2__ {int /*<<< orphan*/  dealloc_driver; } ;
struct ib_device {int /*<<< orphan*/  dev; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ib_unregister_device (struct ib_device*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_device_put (struct ib_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void ib_unregister_device_and_put(struct ib_device *ib_dev)
{
	WARN_ON(!ib_dev->ops.dealloc_driver);
	get_device(&ib_dev->dev);
	ib_device_put(ib_dev);
	__ib_unregister_device(ib_dev);
	put_device(&ib_dev->dev);
}