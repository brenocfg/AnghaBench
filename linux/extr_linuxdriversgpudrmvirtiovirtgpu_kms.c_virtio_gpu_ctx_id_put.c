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
typedef  int /*<<< orphan*/  uint32_t ;
struct virtio_gpu_device {int /*<<< orphan*/  ctx_id_idr_lock; int /*<<< orphan*/  ctx_id_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_gpu_ctx_id_put(struct virtio_gpu_device *vgdev, uint32_t id)
{
	spin_lock(&vgdev->ctx_id_idr_lock);
	idr_remove(&vgdev->ctx_id_idr, id);
	spin_unlock(&vgdev->ctx_id_idr_lock);
}