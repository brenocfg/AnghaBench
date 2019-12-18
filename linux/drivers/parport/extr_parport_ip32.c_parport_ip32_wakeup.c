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
struct parport_ip32_private {int /*<<< orphan*/  irq_complete; } ;
struct parport {TYPE_1__* physport; } ;
struct TYPE_2__ {struct parport_ip32_private* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void parport_ip32_wakeup(struct parport *p)
{
	struct parport_ip32_private * const priv = p->physport->private_data;
	complete(&priv->irq_complete);
}