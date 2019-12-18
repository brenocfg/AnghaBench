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
struct virtio_gpu_device {int /*<<< orphan*/  ctx_id_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtio_gpu_cmd_context_create (struct virtio_gpu_device*,int,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int virtio_gpu_context_create(struct virtio_gpu_device *vgdev,
				      uint32_t nlen, const char *name)
{
	int handle = ida_alloc(&vgdev->ctx_id_ida, GFP_KERNEL);

	if (handle < 0)
		return handle;
	handle += 1;
	virtio_gpu_cmd_context_create(vgdev, handle, nlen, name);
	return handle;
}