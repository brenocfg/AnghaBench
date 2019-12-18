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
typedef  enum xen_irq_type { ____Placeholder_xen_irq_type } xen_irq_type ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 TYPE_1__* info_for_irq (unsigned int) ; 

__attribute__((used)) static enum xen_irq_type type_from_irq(unsigned irq)
{
	return info_for_irq(irq)->type;
}