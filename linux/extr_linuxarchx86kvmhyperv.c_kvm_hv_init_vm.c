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
struct TYPE_3__ {int /*<<< orphan*/  conn_to_evt; int /*<<< orphan*/  hv_lock; } ;
struct TYPE_4__ {TYPE_1__ hyperv; } ;
struct kvm {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void kvm_hv_init_vm(struct kvm *kvm)
{
	mutex_init(&kvm->arch.hyperv.hv_lock);
	idr_init(&kvm->arch.hyperv.conn_to_evt);
}