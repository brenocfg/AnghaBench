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
typedef  scalar_t__ uint32_t ;
struct virtio_gpu_device {int /*<<< orphan*/  ctx_id_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_context_destroy (struct virtio_gpu_device*,scalar_t__) ; 

__attribute__((used)) static void virtio_gpu_context_destroy(struct virtio_gpu_device *vgdev,
				      uint32_t ctx_id)
{
	virtio_gpu_cmd_context_destroy(vgdev, ctx_id);
	ida_free(&vgdev->ctx_id_ida, ctx_id - 1);
}