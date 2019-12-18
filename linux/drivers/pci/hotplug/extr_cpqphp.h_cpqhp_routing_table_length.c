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
struct irq_routing_table {int dummy; } ;
struct irq_info {int dummy; } ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpqhp_routing_table ; 

__attribute__((used)) static inline int cpqhp_routing_table_length(void)
{
	BUG_ON(cpqhp_routing_table == NULL);
	return ((cpqhp_routing_table->size - sizeof(struct irq_routing_table)) /
		sizeof(struct irq_info));
}