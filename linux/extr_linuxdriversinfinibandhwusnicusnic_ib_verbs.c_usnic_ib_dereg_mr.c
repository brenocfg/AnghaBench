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
struct usnic_ib_mr {TYPE_2__* umem; } ;
struct ib_mr {TYPE_1__* uobject; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  va; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct usnic_ib_mr*) ; 
 struct usnic_ib_mr* to_umr (struct ib_mr*) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_uiom_reg_release (TYPE_2__*,int /*<<< orphan*/ ) ; 

int usnic_ib_dereg_mr(struct ib_mr *ibmr)
{
	struct usnic_ib_mr *mr = to_umr(ibmr);

	usnic_dbg("va 0x%lx length 0x%zx\n", mr->umem->va, mr->umem->length);

	usnic_uiom_reg_release(mr->umem, ibmr->uobject->context);
	kfree(mr);
	return 0;
}