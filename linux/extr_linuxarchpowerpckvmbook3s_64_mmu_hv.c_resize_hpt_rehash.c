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
struct kvm_resize_hpt {struct kvm* kvm; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpt; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long kvmppc_hpt_npte (int /*<<< orphan*/ *) ; 
 int resize_hpt_rehash_hpte (struct kvm_resize_hpt*,unsigned long) ; 

__attribute__((used)) static int resize_hpt_rehash(struct kvm_resize_hpt *resize)
{
	struct kvm *kvm = resize->kvm;
	unsigned  long i;
	int rc;

	for (i = 0; i < kvmppc_hpt_npte(&kvm->arch.hpt); i++) {
		rc = resize_hpt_rehash_hpte(resize, i);
		if (rc != 0)
			return rc;
	}

	return 0;
}