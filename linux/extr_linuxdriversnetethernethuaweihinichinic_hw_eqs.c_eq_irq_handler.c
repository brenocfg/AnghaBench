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
struct hinic_eq {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ HINIC_AEQ ; 
 scalar_t__ HINIC_CEQ ; 
 int /*<<< orphan*/  aeq_irq_handler (struct hinic_eq*) ; 
 int /*<<< orphan*/  ceq_irq_handler (struct hinic_eq*) ; 
 int /*<<< orphan*/  eq_update_ci (struct hinic_eq*) ; 

__attribute__((used)) static void eq_irq_handler(void *data)
{
	struct hinic_eq *eq = data;

	if (eq->type == HINIC_AEQ)
		aeq_irq_handler(eq);
	else if (eq->type == HINIC_CEQ)
		ceq_irq_handler(eq);

	eq_update_ci(eq);
}