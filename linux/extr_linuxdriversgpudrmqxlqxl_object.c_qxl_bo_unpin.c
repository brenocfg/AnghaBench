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
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int __qxl_bo_unpin (struct qxl_bo*) ; 
 int qxl_bo_reserve (struct qxl_bo*,int) ; 
 int /*<<< orphan*/  qxl_bo_unreserve (struct qxl_bo*) ; 

int qxl_bo_unpin(struct qxl_bo *bo)
{
	int r;

	r = qxl_bo_reserve(bo, false);
	if (r)
		return r;

	r = __qxl_bo_unpin(bo);
	qxl_bo_unreserve(bo);
	return r;
}