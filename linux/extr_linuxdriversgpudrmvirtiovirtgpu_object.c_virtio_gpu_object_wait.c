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
struct virtio_gpu_object {int /*<<< orphan*/  tbo; } ;

/* Variables and functions */
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 
 int ttm_bo_wait (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ unlikely (int) ; 

int virtio_gpu_object_wait(struct virtio_gpu_object *bo, bool no_wait)
{
	int r;

	r = ttm_bo_reserve(&bo->tbo, true, no_wait, NULL);
	if (unlikely(r != 0))
		return r;
	r = ttm_bo_wait(&bo->tbo, true, no_wait);
	ttm_bo_unreserve(&bo->tbo);
	return r;
}