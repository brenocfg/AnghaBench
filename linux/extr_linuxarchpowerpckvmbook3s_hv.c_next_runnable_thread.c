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
struct kvmppc_vcore {int /*<<< orphan*/ * runnable_threads; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int MAX_SMT_THREADS ; 
 struct kvm_vcpu* READ_ONCE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct kvm_vcpu *next_runnable_thread(struct kvmppc_vcore *vc,
		int *ip)
{
	int i = *ip;
	struct kvm_vcpu *vcpu;

	while (++i < MAX_SMT_THREADS) {
		vcpu = READ_ONCE(vc->runnable_threads[i]);
		if (vcpu) {
			*ip = i;
			return vcpu;
		}
	}
	return NULL;
}