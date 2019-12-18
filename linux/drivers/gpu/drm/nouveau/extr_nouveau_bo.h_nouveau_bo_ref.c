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
struct nouveau_bo {int /*<<< orphan*/  bo; } ;

/* Variables and functions */
 int EINVAL ; 
 struct nouveau_bo* nouveau_bo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_put (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
nouveau_bo_ref(struct nouveau_bo *ref, struct nouveau_bo **pnvbo)
{
	struct nouveau_bo *prev;

	if (!pnvbo)
		return -EINVAL;
	prev = *pnvbo;

	if (ref) {
		ttm_bo_get(&ref->bo);
		*pnvbo = nouveau_bo(&ref->bo);
	} else {
		*pnvbo = NULL;
	}
	if (prev)
		ttm_bo_put(&prev->bo);

	return 0;
}