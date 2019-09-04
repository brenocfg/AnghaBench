#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  tsc_offset; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_l1_tsc_offset ) (struct kvm_vcpu*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_vcpu_write_tsc_offset(struct kvm_vcpu *vcpu, u64 offset)
{
	vcpu->arch.tsc_offset = kvm_x86_ops->write_l1_tsc_offset(vcpu, offset);
}