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
struct kvm_sev_info {int /*<<< orphan*/  asid; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sev_asid_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 

__attribute__((used)) static void sev_asid_free(struct kvm *kvm)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;

	__sev_asid_free(sev->asid);
}