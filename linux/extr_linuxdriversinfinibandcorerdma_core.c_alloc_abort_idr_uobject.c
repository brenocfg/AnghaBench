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
struct ib_uobject {TYPE_2__* ufile; int /*<<< orphan*/  id; TYPE_1__* context; int /*<<< orphan*/  cg_obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  idr_lock; int /*<<< orphan*/  idr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMACG_RESOURCE_HCA_OBJECT ; 
 int /*<<< orphan*/  ib_rdmacg_uncharge (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void alloc_abort_idr_uobject(struct ib_uobject *uobj)
{
	ib_rdmacg_uncharge(&uobj->cg_obj, uobj->context->device,
			   RDMACG_RESOURCE_HCA_OBJECT);

	spin_lock(&uobj->ufile->idr_lock);
	idr_remove(&uobj->ufile->idr, uobj->id);
	spin_unlock(&uobj->ufile->idr_lock);
}