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
struct ucb1x00 {unsigned int io_dir; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IO_DIR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,unsigned int) ; 

void ucb1x00_io_set_dir(struct ucb1x00 *ucb, unsigned int in, unsigned int out)
{
	unsigned long flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_dir |= out;
	ucb->io_dir &= ~in;

	ucb1x00_reg_write(ucb, UCB_IO_DIR, ucb->io_dir);
	spin_unlock_irqrestore(&ucb->io_lock, flags);
}