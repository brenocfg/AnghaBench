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
struct mcb_device {int /*<<< orphan*/  bus; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mcb_device*) ; 
 int /*<<< orphan*/  mcb_bus_put (int /*<<< orphan*/ ) ; 
 struct mcb_device* to_mcb_device (struct device*) ; 

__attribute__((used)) static void mcb_release_dev(struct device *dev)
{
	struct mcb_device *mdev = to_mcb_device(dev);

	mcb_bus_put(mdev->bus);
	kfree(mdev);
}