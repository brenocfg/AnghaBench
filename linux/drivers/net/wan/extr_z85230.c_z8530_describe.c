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
struct z8530_dev {size_t type; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z8530_PORT_OF (unsigned long) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * z8530_type_name ; 

void z8530_describe(struct z8530_dev *dev, char *mapping, unsigned long io)
{
	pr_info("%s: %s found at %s 0x%lX, IRQ %d\n",
		dev->name, 
		z8530_type_name[dev->type],
		mapping,
		Z8530_PORT_OF(io),
		dev->irq);
}