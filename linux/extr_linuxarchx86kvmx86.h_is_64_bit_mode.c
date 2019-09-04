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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_cs_db_l_bits ) (struct kvm_vcpu*,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  is_long_mode (struct kvm_vcpu*) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int*,int*) ; 

__attribute__((used)) static inline bool is_64_bit_mode(struct kvm_vcpu *vcpu)
{
	int cs_db, cs_l;

	if (!is_long_mode(vcpu))
		return false;
	kvm_x86_ops->get_cs_db_l_bits(vcpu, &cs_db, &cs_l);
	return cs_l;
}