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
struct virtio_gpu_object {int /*<<< orphan*/  kmap; int /*<<< orphan*/ * vmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ttm_bo_kunmap (int /*<<< orphan*/ *) ; 

void virtio_gpu_object_kunmap(struct virtio_gpu_object *bo)
{
	bo->vmap = NULL;
	ttm_bo_kunmap(&bo->kmap);
}