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
struct kvm_shared_msrs {int /*<<< orphan*/  urn; scalar_t__ registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_on_user_return (int /*<<< orphan*/ *) ; 
 struct kvm_shared_msrs* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  shared_msrs ; 
 unsigned int smp_processor_id () ; 

__attribute__((used)) static void drop_user_return_notifiers(void)
{
	unsigned int cpu = smp_processor_id();
	struct kvm_shared_msrs *smsr = per_cpu_ptr(shared_msrs, cpu);

	if (smsr->registered)
		kvm_on_user_return(&smsr->urn);
}