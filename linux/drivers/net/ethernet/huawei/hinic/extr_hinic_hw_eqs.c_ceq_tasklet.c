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
struct hinic_eq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eq_irq_handler (struct hinic_eq*) ; 

__attribute__((used)) static void ceq_tasklet(unsigned long ceq_data)
{
	struct hinic_eq *ceq = (struct hinic_eq *)ceq_data;

	eq_irq_handler(ceq);
}