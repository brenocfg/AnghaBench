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
struct nsim_bus_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nsim_dev_remove (struct nsim_bus_dev*) ; 
 struct nsim_bus_dev* to_nsim_bus_dev (struct device*) ; 

__attribute__((used)) static int nsim_bus_remove(struct device *dev)
{
	struct nsim_bus_dev *nsim_bus_dev = to_nsim_bus_dev(dev);

	nsim_dev_remove(nsim_bus_dev);
	return 0;
}