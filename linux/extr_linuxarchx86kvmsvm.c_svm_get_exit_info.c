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
struct vmcb_control_area {int /*<<< orphan*/  exit_info_2; int /*<<< orphan*/  exit_info_1; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_4__ {TYPE_1__* vmcb; } ;
struct TYPE_3__ {struct vmcb_control_area control; } ;

/* Variables and functions */
 TYPE_2__* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void svm_get_exit_info(struct kvm_vcpu *vcpu, u64 *info1, u64 *info2)
{
	struct vmcb_control_area *control = &to_svm(vcpu)->vmcb->control;

	*info1 = control->exit_info_1;
	*info2 = control->exit_info_2;
}