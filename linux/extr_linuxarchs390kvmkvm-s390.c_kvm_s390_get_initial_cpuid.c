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
typedef  int /*<<< orphan*/  u64 ;
struct cpuid {int version; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_cpu_id (struct cpuid*) ; 

__attribute__((used)) static u64 kvm_s390_get_initial_cpuid(void)
{
	struct cpuid cpuid;

	get_cpu_id(&cpuid);
	cpuid.version = 0xff;
	return *((u64 *) &cpuid);
}