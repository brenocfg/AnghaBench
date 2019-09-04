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
struct cpumask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_CALL_FUNC ; 
 int /*<<< orphan*/  ipi_send_msg (struct cpumask const*,int /*<<< orphan*/ ) ; 

void arch_send_call_function_ipi_mask(const struct cpumask *mask)
{
	ipi_send_msg(mask, IPI_CALL_FUNC);
}