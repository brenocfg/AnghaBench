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
struct vlynq_device {TYPE_1__* local; } ;
struct TYPE_2__ {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int VLYNQ_CTRL_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlynq_reset(struct vlynq_device *dev)
{
	writel(readl(&dev->local->control) | VLYNQ_CTRL_RESET,
			&dev->local->control);

	/* Wait for the devices to finish resetting */
	msleep(5);

	/* Remove reset bit */
	writel(readl(&dev->local->control) & ~VLYNQ_CTRL_RESET,
			&dev->local->control);

	/* Give some time for the devices to settle */
	msleep(5);
}