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
struct aac_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  OMR; } ;

/* Variables and functions */
 unsigned long HZ ; 
 unsigned long KERNEL_BOOTING ; 
 unsigned long KERNEL_UP_AND_RUNNING ; 
 TYPE_1__ MUnit ; 
 unsigned long SOFT_RESET_TIME ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  schedule () ; 
 unsigned long src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static bool aac_is_ctrl_up_and_running(struct aac_dev *dev)
{
	bool ctrl_up = true;
	unsigned long status, start;
	bool is_up = false;

	start = jiffies;
	do {
		schedule();
		status = src_readl(dev, MUnit.OMR);

		if (status == 0xffffffff)
			status = 0;

		if (status & KERNEL_BOOTING) {
			start = jiffies;
			continue;
		}

		if (time_after(jiffies, start+HZ*SOFT_RESET_TIME)) {
			ctrl_up = false;
			break;
		}

		is_up = status & KERNEL_UP_AND_RUNNING;

	} while (!is_up);

	return ctrl_up;
}