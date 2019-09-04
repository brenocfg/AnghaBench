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
struct maple_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct maple_device* to_maple_dev (struct device*) ; 
 int /*<<< orphan*/  vmu_disconnect (struct maple_device*) ; 

__attribute__((used)) static int remove_maple_vmu(struct device *dev)
{
	struct maple_device *mdev = to_maple_dev(dev);

	vmu_disconnect(mdev);
	return 0;
}