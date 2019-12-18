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
typedef  scalar_t__ u32 ;
struct xwdt_device {int /*<<< orphan*/  spinlock; scalar_t__ base; } ;

/* Variables and functions */
 int XWT_MAX_SELFTEST_LOOP_COUNT ; 
 scalar_t__ XWT_TBR_OFFSET ; 
 scalar_t__ XWT_TIMER_FAILED ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 xwdt_selftest(struct xwdt_device *xdev)
{
	int i;
	u32 timer_value1;
	u32 timer_value2;

	spin_lock(&xdev->spinlock);

	timer_value1 = ioread32(xdev->base + XWT_TBR_OFFSET);
	timer_value2 = ioread32(xdev->base + XWT_TBR_OFFSET);

	for (i = 0;
		((i <= XWT_MAX_SELFTEST_LOOP_COUNT) &&
			(timer_value2 == timer_value1)); i++) {
		timer_value2 = ioread32(xdev->base + XWT_TBR_OFFSET);
	}

	spin_unlock(&xdev->spinlock);

	if (timer_value2 != timer_value1)
		return ~XWT_TIMER_FAILED;
	else
		return XWT_TIMER_FAILED;
}