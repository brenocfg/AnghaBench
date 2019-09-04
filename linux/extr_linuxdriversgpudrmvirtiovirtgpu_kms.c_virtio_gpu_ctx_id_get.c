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
typedef  int uint32_t ;
struct virtio_gpu_device {int /*<<< orphan*/  ctx_id_idr_lock; int /*<<< orphan*/  ctx_id_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int idr_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_gpu_ctx_id_get(struct virtio_gpu_device *vgdev,
				  uint32_t *resid)
{
	int handle;

	idr_preload(GFP_KERNEL);
	spin_lock(&vgdev->ctx_id_idr_lock);
	handle = idr_alloc(&vgdev->ctx_id_idr, NULL, 1, 0, 0);
	spin_unlock(&vgdev->ctx_id_idr_lock);
	idr_preload_end();
	*resid = handle;
}