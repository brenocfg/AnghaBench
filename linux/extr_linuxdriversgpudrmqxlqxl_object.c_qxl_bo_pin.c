#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct qxl_bo {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int __qxl_bo_pin (struct qxl_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qxl_bo_reserve (struct qxl_bo*,int) ; 
 int /*<<< orphan*/  qxl_bo_unreserve (struct qxl_bo*) ; 

int qxl_bo_pin(struct qxl_bo *bo, u32 domain, u64 *gpu_addr)
{
	int r;

	r = qxl_bo_reserve(bo, false);
	if (r)
		return r;

	r = __qxl_bo_pin(bo, bo->type, NULL);
	qxl_bo_unreserve(bo);
	return r;
}