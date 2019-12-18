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
struct omap_cf_socket {int /*<<< orphan*/  timer; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  omap_cf_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t omap_cf_irq(int irq, void *_cf)
{
	struct omap_cf_socket *cf = (struct omap_cf_socket *)_cf;

	omap_cf_timer(&cf->timer);
	return IRQ_HANDLED;
}