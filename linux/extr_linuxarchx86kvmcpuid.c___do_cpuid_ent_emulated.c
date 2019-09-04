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
typedef  int u32 ;
struct kvm_cpuid_entry2 {int eax; int function; int index; void* ecx; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 void* F (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_CPUID_FLAG_SIGNIFCANT_INDEX ; 
 int /*<<< orphan*/  MOVBE ; 
 int /*<<< orphan*/  RDPID ; 

__attribute__((used)) static int __do_cpuid_ent_emulated(struct kvm_cpuid_entry2 *entry,
				   u32 func, u32 index, int *nent, int maxnent)
{
	switch (func) {
	case 0:
		entry->eax = 7;
		++*nent;
		break;
	case 1:
		entry->ecx = F(MOVBE);
		++*nent;
		break;
	case 7:
		entry->flags |= KVM_CPUID_FLAG_SIGNIFCANT_INDEX;
		if (index == 0)
			entry->ecx = F(RDPID);
		++*nent;
	default:
		break;
	}

	entry->function = func;
	entry->index = index;

	return 0;
}