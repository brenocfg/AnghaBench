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
struct partition_desc {TYPE_1__* parts; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int cpumask_test_cpu (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool partition_check_cpu(struct partition_desc *part,
				unsigned int cpu, unsigned int hwirq)
{
	return cpumask_test_cpu(cpu, &part->parts[hwirq].mask);
}