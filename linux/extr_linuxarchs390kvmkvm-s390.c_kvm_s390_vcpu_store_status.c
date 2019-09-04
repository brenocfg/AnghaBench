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
struct kvm_vcpu {TYPE_5__* run; } ;
struct TYPE_7__ {int /*<<< orphan*/  fpc; } ;
struct TYPE_8__ {TYPE_1__ fpu; } ;
struct TYPE_12__ {TYPE_2__ thread; } ;
struct TYPE_9__ {int /*<<< orphan*/  acrs; int /*<<< orphan*/  fpc; } ;
struct TYPE_10__ {TYPE_3__ regs; } ;
struct TYPE_11__ {TYPE_4__ s; } ;

/* Variables and functions */
 TYPE_6__* current ; 
 int kvm_s390_store_status_unloaded (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  save_access_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_fpu_regs () ; 

int kvm_s390_vcpu_store_status(struct kvm_vcpu *vcpu, unsigned long addr)
{
	/*
	 * The guest FPRS and ACRS are in the host FPRS/ACRS due to the lazy
	 * switch in the run ioctl. Let's update our copies before we save
	 * it into the save area
	 */
	save_fpu_regs();
	vcpu->run->s.regs.fpc = current->thread.fpu.fpc;
	save_access_regs(vcpu->run->s.regs.acrs);

	return kvm_s390_store_status_unloaded(vcpu, addr);
}