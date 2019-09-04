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
struct kvm_rmap_head {int dummy; } ;
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int kvm_zap_rmapp (struct kvm*,struct kvm_rmap_head*) ; 

__attribute__((used)) static int kvm_unmap_rmapp(struct kvm *kvm, struct kvm_rmap_head *rmap_head,
			   struct kvm_memory_slot *slot, gfn_t gfn, int level,
			   unsigned long data)
{
	return kvm_zap_rmapp(kvm, rmap_head);
}