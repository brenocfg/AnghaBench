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
 int /*<<< orphan*/  inb (int) ; 
 int /*<<< orphan*/  io_lock ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u8 slidebar_pos_get(void)
{
	u8 res;
	unsigned long flags;

	spin_lock_irqsave(&io_lock, flags);
	outb(0xf4, 0xff29);
	outb(0xbf, 0xff2a);
	res = inb(0xff2b);
	spin_unlock_irqrestore(&io_lock, flags);

	return res;
}