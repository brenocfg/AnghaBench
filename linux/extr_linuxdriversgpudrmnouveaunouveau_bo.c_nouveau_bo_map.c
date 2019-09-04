#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  num_pages; } ;
struct TYPE_6__ {TYPE_1__ mem; } ;
struct nouveau_bo {TYPE_2__ bo; int /*<<< orphan*/  kmap; } ;

/* Variables and functions */
 int ttm_bo_kmap (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ttm_bo_reserve (TYPE_2__*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (TYPE_2__*) ; 

int
nouveau_bo_map(struct nouveau_bo *nvbo)
{
	int ret;

	ret = ttm_bo_reserve(&nvbo->bo, false, false, NULL);
	if (ret)
		return ret;

	ret = ttm_bo_kmap(&nvbo->bo, 0, nvbo->bo.mem.num_pages, &nvbo->kmap);

	ttm_bo_unreserve(&nvbo->bo);
	return ret;
}