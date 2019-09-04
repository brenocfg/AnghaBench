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
struct gsc_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ GSC_SW_RESET ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int gsc_wait_reset(struct gsc_dev *dev)
{
	unsigned long end = jiffies + msecs_to_jiffies(50);
	u32 cfg;

	while (time_before(jiffies, end)) {
		cfg = readl(dev->regs + GSC_SW_RESET);
		if (!cfg)
			return 0;
		usleep_range(10, 20);
	}

	return -EBUSY;
}