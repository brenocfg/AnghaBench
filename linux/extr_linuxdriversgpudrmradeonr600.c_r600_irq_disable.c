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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  r600_disable_interrupt_state (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_disable_interrupts (struct radeon_device*) ; 
 int /*<<< orphan*/  r600_irq_ack (struct radeon_device*) ; 

void r600_irq_disable(struct radeon_device *rdev)
{
	r600_disable_interrupts(rdev);
	/* Wait and acknowledge irq */
	mdelay(1);
	r600_irq_ack(rdev);
	r600_disable_interrupt_state(rdev);
}