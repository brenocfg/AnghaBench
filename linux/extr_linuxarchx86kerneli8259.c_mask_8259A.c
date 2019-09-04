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
 int /*<<< orphan*/  PIC_MASTER_IMR ; 
 int /*<<< orphan*/  PIC_SLAVE_IMR ; 
 int /*<<< orphan*/  i8259A_lock ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mask_8259A(void)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&i8259A_lock, flags);

	outb(0xff, PIC_MASTER_IMR);	/* mask all of 8259A-1 */
	outb(0xff, PIC_SLAVE_IMR);	/* mask all of 8259A-2 */

	raw_spin_unlock_irqrestore(&i8259A_lock, flags);
}