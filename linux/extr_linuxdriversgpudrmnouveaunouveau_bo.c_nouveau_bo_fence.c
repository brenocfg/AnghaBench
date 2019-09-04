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
struct reservation_object {int dummy; } ;
struct nouveau_fence {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {struct reservation_object* resv; } ;
struct nouveau_bo {TYPE_1__ bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  reservation_object_add_excl_fence (struct reservation_object*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_add_shared_fence (struct reservation_object*,int /*<<< orphan*/ *) ; 

void
nouveau_bo_fence(struct nouveau_bo *nvbo, struct nouveau_fence *fence, bool exclusive)
{
	struct reservation_object *resv = nvbo->bo.resv;

	if (exclusive)
		reservation_object_add_excl_fence(resv, &fence->base);
	else if (fence)
		reservation_object_add_shared_fence(resv, &fence->base);
}