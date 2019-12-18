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
struct TYPE_2__ {int /*<<< orphan*/  id; } ;
struct nsim_bus_dev {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nsim_bus_dev*) ; 
 int /*<<< orphan*/  nsim_bus_dev_ids ; 

__attribute__((used)) static void nsim_bus_dev_del(struct nsim_bus_dev *nsim_bus_dev)
{
	device_unregister(&nsim_bus_dev->dev);
	ida_free(&nsim_bus_dev_ids, nsim_bus_dev->dev.id);
	kfree(nsim_bus_dev);
}