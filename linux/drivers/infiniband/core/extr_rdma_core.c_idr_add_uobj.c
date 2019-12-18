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
struct ib_uobject {int /*<<< orphan*/  id; TYPE_1__* ufile; } ;
struct TYPE_2__ {int /*<<< orphan*/  idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int xa_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xa_limit_32b ; 

__attribute__((used)) static int idr_add_uobj(struct ib_uobject *uobj)
{
       /*
        * We start with allocating an idr pointing to NULL. This represents an
        * object which isn't initialized yet. We'll replace it later on with
        * the real object once we commit.
        */
	return xa_alloc(&uobj->ufile->idr, &uobj->id, NULL, xa_limit_32b,
			GFP_KERNEL);
}