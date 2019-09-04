#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {scalar_t__ nr_hw_wp; scalar_t__ nr_hw_bp; unsigned long last_bp; } ;
struct TYPE_12__ {TYPE_5__ guestdbg; TYPE_4__* sie_block; } ;
struct kvm_vcpu {TYPE_6__ arch; TYPE_2__* run; } ;
struct kvm_hw_wp_info_arch {unsigned long addr; } ;
struct kvm_hw_bp_info_arch {int dummy; } ;
struct kvm_debug_exit_arch {unsigned long addr; void* type; } ;
struct TYPE_9__ {unsigned long addr; } ;
struct TYPE_10__ {TYPE_3__ gpsw; } ;
struct TYPE_7__ {struct kvm_debug_exit_arch arch; } ;
struct TYPE_8__ {TYPE_1__ debug; } ;

/* Variables and functions */
 void* KVM_HW_BP ; 
 void* KVM_HW_WP_WRITE ; 
 void* KVM_SINGLESTEP ; 
 struct kvm_hw_wp_info_arch* any_wp_changed (struct kvm_vcpu*) ; 
 struct kvm_hw_bp_info_arch* find_hw_bp (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ guestdbg_hw_bp_enabled (struct kvm_vcpu*) ; 
 scalar_t__ guestdbg_sstep_enabled (struct kvm_vcpu*) ; 
 scalar_t__ per_bp_event (int /*<<< orphan*/ ) ; 
 scalar_t__ per_write_wp_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debug_exit_required(struct kvm_vcpu *vcpu, u8 perc,
			       unsigned long peraddr)
{
	struct kvm_debug_exit_arch *debug_exit = &vcpu->run->debug.arch;
	struct kvm_hw_wp_info_arch *wp_info = NULL;
	struct kvm_hw_bp_info_arch *bp_info = NULL;
	unsigned long addr = vcpu->arch.sie_block->gpsw.addr;

	if (guestdbg_hw_bp_enabled(vcpu)) {
		if (per_write_wp_event(perc) &&
		    vcpu->arch.guestdbg.nr_hw_wp > 0) {
			wp_info = any_wp_changed(vcpu);
			if (wp_info) {
				debug_exit->addr = wp_info->addr;
				debug_exit->type = KVM_HW_WP_WRITE;
				goto exit_required;
			}
		}
		if (per_bp_event(perc) &&
			 vcpu->arch.guestdbg.nr_hw_bp > 0) {
			bp_info = find_hw_bp(vcpu, addr);
			/* remove duplicate events if PC==PER address */
			if (bp_info && (addr != peraddr)) {
				debug_exit->addr = addr;
				debug_exit->type = KVM_HW_BP;
				vcpu->arch.guestdbg.last_bp = addr;
				goto exit_required;
			}
			/* breakpoint missed */
			bp_info = find_hw_bp(vcpu, peraddr);
			if (bp_info && vcpu->arch.guestdbg.last_bp != peraddr) {
				debug_exit->addr = peraddr;
				debug_exit->type = KVM_HW_BP;
				goto exit_required;
			}
		}
	}
	if (guestdbg_sstep_enabled(vcpu) && per_bp_event(perc)) {
		debug_exit->addr = addr;
		debug_exit->type = KVM_SINGLESTEP;
		goto exit_required;
	}

	return 0;
exit_required:
	return 1;
}