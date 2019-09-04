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
struct openpic {TYPE_2__* kvm; struct openpic* private; } ;
struct kvm_device {TYPE_2__* kvm; struct kvm_device* private; } ;
struct TYPE_3__ {int /*<<< orphan*/ * mpic; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct openpic*) ; 

__attribute__((used)) static void mpic_destroy(struct kvm_device *dev)
{
	struct openpic *opp = dev->private;

	dev->kvm->arch.mpic = NULL;
	kfree(opp);
	kfree(dev);
}