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
struct guc_policy {scalar_t__ policy_flags; int /*<<< orphan*/  fault_time; int /*<<< orphan*/  preemption_time; int /*<<< orphan*/  execution_quantum; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLICY_DEFAULT_EXECUTION_QUANTUM_US ; 
 int /*<<< orphan*/  POLICY_DEFAULT_FAULT_TIME_US ; 
 int /*<<< orphan*/  POLICY_DEFAULT_PREEMPTION_TIME_US ; 

__attribute__((used)) static void guc_policy_init(struct guc_policy *policy)
{
	policy->execution_quantum = POLICY_DEFAULT_EXECUTION_QUANTUM_US;
	policy->preemption_time = POLICY_DEFAULT_PREEMPTION_TIME_US;
	policy->fault_time = POLICY_DEFAULT_FAULT_TIME_US;
	policy->policy_flags = 0;
}