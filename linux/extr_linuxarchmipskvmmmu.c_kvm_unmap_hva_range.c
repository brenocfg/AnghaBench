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
struct kvm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* flush_shadow_all ) (struct kvm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  handle_hva_to_gpa (struct kvm*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* kvm_mips_callbacks ; 
 int /*<<< orphan*/  kvm_unmap_hva_handler ; 
 int /*<<< orphan*/  stub1 (struct kvm*) ; 

int kvm_unmap_hva_range(struct kvm *kvm, unsigned long start, unsigned long end)
{
	handle_hva_to_gpa(kvm, start, end, &kvm_unmap_hva_handler, NULL);

	kvm_mips_callbacks->flush_shadow_all(kvm);
	return 0;
}