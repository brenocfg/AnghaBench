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
struct vfio_group {int /*<<< orphan*/  notifier; struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_GROUP_NOTIFY_SET_KVM ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kvm*) ; 

void vfio_group_set_kvm(struct vfio_group *group, struct kvm *kvm)
{
	group->kvm = kvm;
	blocking_notifier_call_chain(&group->notifier,
				VFIO_GROUP_NOTIFY_SET_KVM, kvm);
}