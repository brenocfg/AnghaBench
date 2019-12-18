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
struct ttm_range_manager {int /*<<< orphan*/  lock; int /*<<< orphan*/  mm; } ;
struct ttm_mem_type_manager {struct ttm_range_manager* priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_mm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct ttm_range_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ttm_bo_man_init(struct ttm_mem_type_manager *man,
			   unsigned long p_size)
{
	struct ttm_range_manager *rman;

	rman = kzalloc(sizeof(*rman), GFP_KERNEL);
	if (!rman)
		return -ENOMEM;

	drm_mm_init(&rman->mm, 0, p_size);
	spin_lock_init(&rman->lock);
	man->priv = rman;
	return 0;
}