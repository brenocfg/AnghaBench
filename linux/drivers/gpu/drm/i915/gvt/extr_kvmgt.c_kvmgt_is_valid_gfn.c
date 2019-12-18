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
struct kvmgt_guest_info {struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_valid (unsigned long) ; 
 int kvm_is_visible_gfn (struct kvm*,unsigned long) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool kvmgt_is_valid_gfn(unsigned long handle, unsigned long gfn)
{
	struct kvmgt_guest_info *info;
	struct kvm *kvm;
	int idx;
	bool ret;

	if (!handle_valid(handle))
		return false;

	info = (struct kvmgt_guest_info *)handle;
	kvm = info->kvm;

	idx = srcu_read_lock(&kvm->srcu);
	ret = kvm_is_visible_gfn(kvm, gfn);
	srcu_read_unlock(&kvm->srcu, idx);

	return ret;
}