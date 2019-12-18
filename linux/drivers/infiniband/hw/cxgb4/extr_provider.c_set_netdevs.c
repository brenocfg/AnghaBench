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
struct ib_device {int dummy; } ;
struct TYPE_2__ {int nports; int /*<<< orphan*/ * ports; } ;
struct c4iw_rdev {TYPE_1__ lldi; } ;

/* Variables and functions */
 int ib_device_set_netdev (struct ib_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_netdevs(struct ib_device *ib_dev, struct c4iw_rdev *rdev)
{
	int ret;
	int i;

	for (i = 0; i < rdev->lldi.nports; i++) {
		ret = ib_device_set_netdev(ib_dev, rdev->lldi.ports[i],
					   i + 1);
		if (ret)
			return ret;
	}
	return 0;
}