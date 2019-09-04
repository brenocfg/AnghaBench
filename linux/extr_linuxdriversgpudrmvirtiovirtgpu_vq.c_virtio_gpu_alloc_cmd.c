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
struct virtio_gpu_vbuffer {void* buf; } ;
struct virtio_gpu_device {int dummy; } ;
struct virtio_gpu_ctrl_hdr {int dummy; } ;

/* Variables and functions */
 void* ERR_CAST (struct virtio_gpu_vbuffer*) ; 
 scalar_t__ IS_ERR (struct virtio_gpu_vbuffer*) ; 
 struct virtio_gpu_vbuffer* virtio_gpu_get_vbuf (struct virtio_gpu_device*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *virtio_gpu_alloc_cmd(struct virtio_gpu_device *vgdev,
				  struct virtio_gpu_vbuffer **vbuffer_p,
				  int size)
{
	struct virtio_gpu_vbuffer *vbuf;

	vbuf = virtio_gpu_get_vbuf(vgdev, size,
				   sizeof(struct virtio_gpu_ctrl_hdr),
				   NULL, NULL);
	if (IS_ERR(vbuf)) {
		*vbuffer_p = NULL;
		return ERR_CAST(vbuf);
	}
	*vbuffer_p = vbuf;
	return vbuf->buf;
}