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
struct TYPE_2__ {int /*<<< orphan*/  virt; } ;
struct kvm_resize_hpt {TYPE_1__ hpt; int /*<<< orphan*/  order; } ;

/* Variables and functions */
 int kvmppc_allocate_hpt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resize_hpt_debug (struct kvm_resize_hpt*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int resize_hpt_allocate(struct kvm_resize_hpt *resize)
{
	int rc;

	rc = kvmppc_allocate_hpt(&resize->hpt, resize->order);
	if (rc < 0)
		return rc;

	resize_hpt_debug(resize, "resize_hpt_allocate(): HPT @ 0x%lx\n",
			 resize->hpt.virt);

	return 0;
}