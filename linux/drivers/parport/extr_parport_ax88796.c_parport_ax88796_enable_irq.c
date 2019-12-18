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
struct parport {int /*<<< orphan*/  irq; } ;
struct ax_drvdata {int irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct ax_drvdata* pp_to_drv (struct parport*) ; 

__attribute__((used)) static void
parport_ax88796_enable_irq(struct parport *p)
{
	struct ax_drvdata *dd = pp_to_drv(p);
	unsigned long flags;

	local_irq_save(flags);
	if (!dd->irq_enabled) {
		enable_irq(p->irq);
		dd->irq_enabled = 1;
	}
	local_irq_restore(flags);
}