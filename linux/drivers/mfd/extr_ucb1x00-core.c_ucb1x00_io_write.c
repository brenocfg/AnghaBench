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
struct ucb1x00 {unsigned int io_out; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCB_IO_DATA ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ucb1x00_reg_write (struct ucb1x00*,int /*<<< orphan*/ ,unsigned int) ; 

void ucb1x00_io_write(struct ucb1x00 *ucb, unsigned int set, unsigned int clear)
{
	unsigned long flags;

	spin_lock_irqsave(&ucb->io_lock, flags);
	ucb->io_out |= set;
	ucb->io_out &= ~clear;

	ucb1x00_reg_write(ucb, UCB_IO_DATA, ucb->io_out);
	spin_unlock_irqrestore(&ucb->io_lock, flags);
}