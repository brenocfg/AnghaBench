#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bank_lock; } ;
typedef  TYPE_1__ mace_private ;

/* Variables and functions */
 int /*<<< orphan*/  AM2150_MACE_BASE ; 
 int /*<<< orphan*/  MACEBANK (int) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mace_write(mace_private *lp, unsigned int ioaddr, int reg,
		       int data)
{
  unsigned long flags;

  switch (reg >> 4) {
    case 0: /* register 0-15 */
      outb(data & 0xFF, ioaddr + AM2150_MACE_BASE + reg);
      break;
    case 1: /* register 16-31 */
      spin_lock_irqsave(&lp->bank_lock, flags);
      MACEBANK(1);
      outb(data & 0xFF, ioaddr + AM2150_MACE_BASE + (reg & 0x0F));
      MACEBANK(0);
      spin_unlock_irqrestore(&lp->bank_lock, flags);
      break;
  }
}