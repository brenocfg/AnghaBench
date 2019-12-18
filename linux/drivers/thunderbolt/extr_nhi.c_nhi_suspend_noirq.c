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
struct device {int dummy; } ;

/* Variables and functions */
 int __nhi_suspend_noirq (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_may_wakeup (struct device*) ; 

__attribute__((used)) static int nhi_suspend_noirq(struct device *dev)
{
	return __nhi_suspend_noirq(dev, device_may_wakeup(dev));
}