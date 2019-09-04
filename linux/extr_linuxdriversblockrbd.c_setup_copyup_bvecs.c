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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct rbd_obj_request {size_t copyup_bvec_count; TYPE_1__* copyup_bvecs; } ;
struct TYPE_2__ {unsigned int bv_len; scalar_t__ bv_offset; int /*<<< orphan*/  bv_page; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 size_t calc_pages_for (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 unsigned int min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 

__attribute__((used)) static int setup_copyup_bvecs(struct rbd_obj_request *obj_req, u64 obj_overlap)
{
	u32 i;

	rbd_assert(!obj_req->copyup_bvecs);
	obj_req->copyup_bvec_count = calc_pages_for(0, obj_overlap);
	obj_req->copyup_bvecs = kcalloc(obj_req->copyup_bvec_count,
					sizeof(*obj_req->copyup_bvecs),
					GFP_NOIO);
	if (!obj_req->copyup_bvecs)
		return -ENOMEM;

	for (i = 0; i < obj_req->copyup_bvec_count; i++) {
		unsigned int len = min(obj_overlap, (u64)PAGE_SIZE);

		obj_req->copyup_bvecs[i].bv_page = alloc_page(GFP_NOIO);
		if (!obj_req->copyup_bvecs[i].bv_page)
			return -ENOMEM;

		obj_req->copyup_bvecs[i].bv_offset = 0;
		obj_req->copyup_bvecs[i].bv_len = len;
		obj_overlap -= len;
	}

	rbd_assert(!obj_overlap);
	return 0;
}