#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nr_hw_bp; int nr_hw_wp; struct kvm_hw_wp_info_arch* hw_wp_info; struct kvm_hw_wp_info_arch* hw_bp_info; } ;
struct TYPE_6__ {TYPE_2__ guestdbg; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_hw_wp_info_arch {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct kvm_hw_breakpoint {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct kvm_hw_bp_info_arch {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int nr_hw_bp; int /*<<< orphan*/  hw_bp; } ;
struct kvm_guest_debug {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct kvm_hw_wp_info_arch*) ; 
#define  KVM_HW_BP 129 
#define  KVM_HW_WP_WRITE 128 
 int MAX_BP_COUNT ; 
 int PTR_ERR (struct kvm_hw_wp_info_arch*) ; 
 int __import_wp_info (struct kvm_vcpu*,struct kvm_hw_wp_info_arch*,struct kvm_hw_wp_info_arch*) ; 
 int /*<<< orphan*/  kfree (struct kvm_hw_wp_info_arch*) ; 
 struct kvm_hw_wp_info_arch* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct kvm_hw_wp_info_arch* memdup_user (int /*<<< orphan*/ ,int) ; 

int kvm_s390_import_bp_data(struct kvm_vcpu *vcpu,
			    struct kvm_guest_debug *dbg)
{
	int ret = 0, nr_wp = 0, nr_bp = 0, i;
	struct kvm_hw_breakpoint *bp_data = NULL;
	struct kvm_hw_wp_info_arch *wp_info = NULL;
	struct kvm_hw_bp_info_arch *bp_info = NULL;

	if (dbg->arch.nr_hw_bp <= 0 || !dbg->arch.hw_bp)
		return 0;
	else if (dbg->arch.nr_hw_bp > MAX_BP_COUNT)
		return -EINVAL;

	bp_data = memdup_user(dbg->arch.hw_bp,
			      sizeof(*bp_data) * dbg->arch.nr_hw_bp);
	if (IS_ERR(bp_data))
		return PTR_ERR(bp_data);

	for (i = 0; i < dbg->arch.nr_hw_bp; i++) {
		switch (bp_data[i].type) {
		case KVM_HW_WP_WRITE:
			nr_wp++;
			break;
		case KVM_HW_BP:
			nr_bp++;
			break;
		default:
			break;
		}
	}

	if (nr_wp > 0) {
		wp_info = kmalloc_array(nr_wp,
					sizeof(*wp_info),
					GFP_KERNEL);
		if (!wp_info) {
			ret = -ENOMEM;
			goto error;
		}
	}
	if (nr_bp > 0) {
		bp_info = kmalloc_array(nr_bp,
					sizeof(*bp_info),
					GFP_KERNEL);
		if (!bp_info) {
			ret = -ENOMEM;
			goto error;
		}
	}

	for (nr_wp = 0, nr_bp = 0, i = 0; i < dbg->arch.nr_hw_bp; i++) {
		switch (bp_data[i].type) {
		case KVM_HW_WP_WRITE:
			ret = __import_wp_info(vcpu, &bp_data[i],
					       &wp_info[nr_wp]);
			if (ret)
				goto error;
			nr_wp++;
			break;
		case KVM_HW_BP:
			bp_info[nr_bp].len = bp_data[i].len;
			bp_info[nr_bp].addr = bp_data[i].addr;
			nr_bp++;
			break;
		}
	}

	vcpu->arch.guestdbg.nr_hw_bp = nr_bp;
	vcpu->arch.guestdbg.hw_bp_info = bp_info;
	vcpu->arch.guestdbg.nr_hw_wp = nr_wp;
	vcpu->arch.guestdbg.hw_wp_info = wp_info;
	return 0;
error:
	kfree(bp_data);
	kfree(wp_info);
	kfree(bp_info);
	return ret;
}