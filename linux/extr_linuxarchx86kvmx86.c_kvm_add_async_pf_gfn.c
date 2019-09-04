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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * gfns; } ;
struct TYPE_4__ {TYPE_1__ apf; } ;
struct kvm_vcpu {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 size_t kvm_async_pf_hash_fn (int /*<<< orphan*/ ) ; 
 size_t kvm_async_pf_next_probe (size_t) ; 

__attribute__((used)) static void kvm_add_async_pf_gfn(struct kvm_vcpu *vcpu, gfn_t gfn)
{
	u32 key = kvm_async_pf_hash_fn(gfn);

	while (vcpu->arch.apf.gfns[key] != ~0)
		key = kvm_async_pf_next_probe(key);

	vcpu->arch.apf.gfns[key] = gfn;
}