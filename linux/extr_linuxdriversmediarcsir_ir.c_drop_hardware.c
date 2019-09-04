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

/* Variables and functions */
 scalar_t__ UART_IER ; 
 int /*<<< orphan*/  hardware_lock ; 
 scalar_t__ io ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void drop_hardware(void)
{
	unsigned long flags;

	spin_lock_irqsave(&hardware_lock, flags);

	/* turn off interrupts */
	outb(0, io + UART_IER);

	spin_unlock_irqrestore(&hardware_lock, flags);
}