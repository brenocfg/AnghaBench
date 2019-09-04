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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int (* cpu_on ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  cpu_logical_map (unsigned int) ; 
 TYPE_1__ psci_ops ; 
 int /*<<< orphan*/  secondary_startup ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_idmap (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psci_boot_secondary(unsigned int cpu, struct task_struct *idle)
{
	if (psci_ops.cpu_on)
		return psci_ops.cpu_on(cpu_logical_map(cpu),
					virt_to_idmap(&secondary_startup));
	return -ENODEV;
}