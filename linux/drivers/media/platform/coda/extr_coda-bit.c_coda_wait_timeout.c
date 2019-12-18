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
struct coda_dev {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ coda_isbusy (struct coda_dev*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int coda_wait_timeout(struct coda_dev *dev)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(1000);

	while (coda_isbusy(dev)) {
		if (time_after(jiffies, timeout))
			return -ETIMEDOUT;
	}
	return 0;
}