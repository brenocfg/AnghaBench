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
struct kvm_page_track_notifier_head {int /*<<< orphan*/  track_srcu; } ;
struct TYPE_2__ {struct kvm_page_track_notifier_head track_notifier_head; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 

void kvm_page_track_cleanup(struct kvm *kvm)
{
	struct kvm_page_track_notifier_head *head;

	head = &kvm->arch.track_notifier_head;
	cleanup_srcu_struct(&head->track_srcu);
}