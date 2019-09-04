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
typedef  int /*<<< orphan*/  u32 ;
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hibmc_tt_backend_func ; 
 int /*<<< orphan*/  kfree (struct ttm_tt*) ; 
 struct ttm_tt* kzalloc (int,int /*<<< orphan*/ ) ; 
 int ttm_tt_init (struct ttm_tt*,struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ttm_tt *hibmc_ttm_tt_create(struct ttm_buffer_object *bo,
					  u32 page_flags)
{
	struct ttm_tt *tt;
	int ret;

	tt = kzalloc(sizeof(*tt), GFP_KERNEL);
	if (!tt) {
		DRM_ERROR("failed to allocate ttm_tt\n");
		return NULL;
	}
	tt->func = &hibmc_tt_backend_func;
	ret = ttm_tt_init(tt, bo, page_flags);
	if (ret) {
		DRM_ERROR("failed to initialize ttm_tt: %d\n", ret);
		kfree(tt);
		return NULL;
	}
	return tt;
}