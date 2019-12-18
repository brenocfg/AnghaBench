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
struct hp100_private {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  CRC ; 
 int /*<<< orphan*/  DROPPED ; 
 int /*<<< orphan*/  MAC_CTRL ; 
 int /*<<< orphan*/  PERFORMANCE ; 
 int /*<<< orphan*/  TRACE ; 
 TYPE_1__* dev ; 
 int /*<<< orphan*/  hp100_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hp100_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hp100_clear_stats(struct hp100_private *lp, int ioaddr)
{
	unsigned long flags;

#ifdef HP100_DEBUG_B
	hp100_outw(0x4217, TRACE);
	printk("hp100: %s: clear_stats\n", dev->name);
#endif

	spin_lock_irqsave(&lp->lock, flags);
	hp100_page(MAC_CTRL);	/* get all statistics bytes */
	hp100_inw(DROPPED);
	hp100_inb(CRC);
	hp100_inb(ABORT);
	hp100_page(PERFORMANCE);
	spin_unlock_irqrestore(&lp->lock, flags);
}