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
struct ast_bo {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,struct ast_bo*) ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int ast_bo_reserve(struct ast_bo *bo, bool no_wait)
{
	int ret;

	ret = ttm_bo_reserve(&bo->bo, true, no_wait, NULL);
	if (ret) {
		if (ret != -ERESTARTSYS && ret != -EBUSY)
			DRM_ERROR("reserve failed %p\n", bo);
		return ret;
	}
	return 0;
}