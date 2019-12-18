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
struct intc_irqpin_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  intc_irqpin_lock ; 
 unsigned long intc_irqpin_read (struct intc_irqpin_priv*,int) ; 
 int /*<<< orphan*/  intc_irqpin_write (struct intc_irqpin_priv*,int,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void intc_irqpin_read_modify_write(struct intc_irqpin_priv *p,
					  int reg, int shift,
					  int width, int value)
{
	unsigned long flags;
	unsigned long tmp;

	raw_spin_lock_irqsave(&intc_irqpin_lock, flags);

	tmp = intc_irqpin_read(p, reg);
	tmp &= ~(((1 << width) - 1) << shift);
	tmp |= value << shift;
	intc_irqpin_write(p, reg, tmp);

	raw_spin_unlock_irqrestore(&intc_irqpin_lock, flags);
}