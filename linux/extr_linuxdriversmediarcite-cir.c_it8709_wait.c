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
struct ite_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IT8709_IDLE ; 
 int /*<<< orphan*/  IT8709_MODE ; 
 scalar_t__ it8709_rm (struct ite_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void it8709_wait(struct ite_dev *dev)
{
	int i = 0;
	/*
	 * loop until device tells it's ready to continue
	 * iterations count is usually ~750 but can sometimes achieve 13000
	 */
	for (i = 0; i < 15000; i++) {
		udelay(2);
		if (it8709_rm(dev, IT8709_MODE) == IT8709_IDLE)
			break;
	}
}