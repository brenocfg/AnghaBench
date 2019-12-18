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
struct virtio_gpu_device {int /*<<< orphan*/  resource_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int virtio_gpu_resource_id_get(struct virtio_gpu_device *vgdev,
				       uint32_t *resid)
{
#if 0
	int handle = ida_alloc(&vgdev->resource_ida, GFP_KERNEL);

	if (handle < 0)
		return handle;
#else
	static int handle;

	/*
	 * FIXME: dirty hack to avoid re-using IDs, virglrenderer
	 * can't deal with that.  Needs fixing in virglrenderer, also
	 * should figure a better way to handle that in the guest.
	 */
	handle++;
#endif

	*resid = handle + 1;
	return 0;
}