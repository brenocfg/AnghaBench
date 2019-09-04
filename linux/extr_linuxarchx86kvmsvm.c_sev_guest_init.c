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
struct kvm_sev_info {int active; int asid; int /*<<< orphan*/  regions_list; } ;
struct kvm_sev_cmd {int /*<<< orphan*/  error; } ;
struct kvm {int dummy; } ;
struct TYPE_2__ {struct kvm_sev_info sev_info; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __sev_asid_free (int) ; 
 int sev_asid_new () ; 
 int sev_platform_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* to_kvm_svm (struct kvm*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sev_guest_init(struct kvm *kvm, struct kvm_sev_cmd *argp)
{
	struct kvm_sev_info *sev = &to_kvm_svm(kvm)->sev_info;
	int asid, ret;

	ret = -EBUSY;
	if (unlikely(sev->active))
		return ret;

	asid = sev_asid_new();
	if (asid < 0)
		return ret;

	ret = sev_platform_init(&argp->error);
	if (ret)
		goto e_free;

	sev->active = true;
	sev->asid = asid;
	INIT_LIST_HEAD(&sev->regions_list);

	return 0;

e_free:
	__sev_asid_free(asid);
	return ret;
}