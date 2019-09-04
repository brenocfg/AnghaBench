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
 int /*<<< orphan*/  ttm_bo_unreserve (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void virtio_gpu_object_unreserve(struct virtio_gpu_object *bo)
{
	ttm_bo_unreserve(&bo->tbo);
}