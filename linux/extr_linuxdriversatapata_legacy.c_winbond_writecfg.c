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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  winbond_lock ; 

__attribute__((used)) static void winbond_writecfg(unsigned long port, u8 reg, u8 val)
{
	unsigned long flags;
	spin_lock_irqsave(&winbond_lock, flags);
	outb(reg, port + 0x01);
	outb(val, port + 0x02);
	spin_unlock_irqrestore(&winbond_lock, flags);
}