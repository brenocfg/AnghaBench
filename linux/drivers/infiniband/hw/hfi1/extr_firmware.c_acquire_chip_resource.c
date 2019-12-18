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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int __acquire_chip_resource (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int acquire_chip_resource(struct hfi1_devdata *dd, u32 resource, u32 mswait)
{
	unsigned long timeout;
	int ret;

	timeout = jiffies + msecs_to_jiffies(mswait);
	while (1) {
		ret = __acquire_chip_resource(dd, resource);
		if (ret != -EBUSY)
			return ret;
		/* resource is busy, check our timeout */
		if (time_after_eq(jiffies, timeout))
			return -EBUSY;
		usleep_range(80, 120);	/* arbitrary delay */
	}
}