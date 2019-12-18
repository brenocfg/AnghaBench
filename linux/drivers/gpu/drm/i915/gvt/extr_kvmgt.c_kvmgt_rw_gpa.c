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
struct kvmgt_guest_info {struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  mm; int /*<<< orphan*/  srcu; } ;
struct TYPE_2__ {int /*<<< orphan*/ * mm; } ;

/* Variables and functions */
 int EFAULT ; 
 int ESRCH ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  handle_valid (unsigned long) ; 
 int kvm_read_guest (struct kvm*,unsigned long,void*,unsigned long) ; 
 int kvm_write_guest (struct kvm*,unsigned long,void*,unsigned long) ; 
 int /*<<< orphan*/  mmget_not_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmput (int /*<<< orphan*/ ) ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  unuse_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_mm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmgt_rw_gpa(unsigned long handle, unsigned long gpa,
			void *buf, unsigned long len, bool write)
{
	struct kvmgt_guest_info *info;
	struct kvm *kvm;
	int idx, ret;
	bool kthread = current->mm == NULL;

	if (!handle_valid(handle))
		return -ESRCH;

	info = (struct kvmgt_guest_info *)handle;
	kvm = info->kvm;

	if (kthread) {
		if (!mmget_not_zero(kvm->mm))
			return -EFAULT;
		use_mm(kvm->mm);
	}

	idx = srcu_read_lock(&kvm->srcu);
	ret = write ? kvm_write_guest(kvm, gpa, buf, len) :
		      kvm_read_guest(kvm, gpa, buf, len);
	srcu_read_unlock(&kvm->srcu, idx);

	if (kthread) {
		unuse_mm(kvm->mm);
		mmput(kvm->mm);
	}

	return ret;
}