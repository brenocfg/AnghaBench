#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dev; } ;
struct virtio_gpu_object {TYPE_2__ gem_base; int /*<<< orphan*/  tbo; } ;
struct virtio_gpu_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct virtio_gpu_device* dev_private; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct virtio_gpu_object*) ; 
 int ttm_bo_reserve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int virtio_gpu_object_reserve(struct virtio_gpu_object *bo,
					 bool no_wait)
{
	int r;

	r = ttm_bo_reserve(&bo->tbo, true, no_wait, NULL);
	if (unlikely(r != 0)) {
		if (r != -ERESTARTSYS) {
			struct virtio_gpu_device *qdev =
				bo->gem_base.dev->dev_private;
			dev_err(qdev->dev, "%p reserve failed\n", bo);
		}
		return r;
	}
	return 0;
}