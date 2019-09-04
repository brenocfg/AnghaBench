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
struct lp8788 {int /*<<< orphan*/  irqdm; scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,int /*<<< orphan*/ ) ; 

void lp8788_irq_exit(struct lp8788 *lp)
{
	if (lp->irq)
		free_irq(lp->irq, lp->irqdm);
}