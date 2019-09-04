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
struct vc4_bo {scalar_t__ madv; int /*<<< orphan*/  madv_lock; int /*<<< orphan*/  usecnt; } ;

/* Variables and functions */
 scalar_t__ VC4_MADV_DONTNEED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_not_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc4_bo_add_to_purgeable_pool (struct vc4_bo*) ; 

void vc4_bo_dec_usecnt(struct vc4_bo *bo)
{
	/* Fast path: if the BO is still retained by someone, no need to test
	 * the madv value.
	 */
	if (refcount_dec_not_one(&bo->usecnt))
		return;

	mutex_lock(&bo->madv_lock);
	if (refcount_dec_and_test(&bo->usecnt) &&
	    bo->madv == VC4_MADV_DONTNEED)
		vc4_bo_add_to_purgeable_pool(bo);
	mutex_unlock(&bo->madv_lock);
}