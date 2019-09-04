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
struct sm501_devdata {int /*<<< orphan*/  irq; } ;
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; int /*<<< orphan*/ * parent; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_IRQ ; 

__attribute__((used)) static void sm501_create_irq(struct sm501_devdata *sm,
			     struct resource *res)
{
	res->flags = IORESOURCE_IRQ;
	res->parent = NULL;
	res->start = res->end = sm->irq;
}