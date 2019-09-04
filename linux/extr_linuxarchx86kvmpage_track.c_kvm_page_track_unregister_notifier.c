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
struct kvm_page_track_notifier_node {int /*<<< orphan*/  node; } ;
struct kvm_page_track_notifier_head {int /*<<< orphan*/  track_srcu; } ;
struct TYPE_2__ {struct kvm_page_track_notifier_head track_notifier_head; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

void
kvm_page_track_unregister_notifier(struct kvm *kvm,
				   struct kvm_page_track_notifier_node *n)
{
	struct kvm_page_track_notifier_head *head;

	head = &kvm->arch.track_notifier_head;

	spin_lock(&kvm->mmu_lock);
	hlist_del_rcu(&n->node);
	spin_unlock(&kvm->mmu_lock);
	synchronize_srcu(&head->track_srcu);
}