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
struct irq_data {int irq; } ;

/* Variables and functions */
 int AU1000_INTC1_INT_BASE ; 
 int /*<<< orphan*/  AU1000_SYS_WAKEMSK ; 
 int EINVAL ; 
 unsigned long alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int au1x_ic1_setwake(struct irq_data *d, unsigned int on)
{
	int bit = d->irq - AU1000_INTC1_INT_BASE;
	unsigned long wakemsk, flags;

	/* only GPIO 0-7 can act as wakeup source.  Fortunately these
	 * are wired up identically on all supported variants.
	 */
	if ((bit < 0) || (bit > 7))
		return -EINVAL;

	local_irq_save(flags);
	wakemsk = alchemy_rdsys(AU1000_SYS_WAKEMSK);
	if (on)
		wakemsk |= 1 << bit;
	else
		wakemsk &= ~(1 << bit);
	alchemy_wrsys(wakemsk, AU1000_SYS_WAKEMSK);
	local_irq_restore(flags);

	return 0;
}