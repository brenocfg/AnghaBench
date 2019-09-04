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
typedef  int /*<<< orphan*/  virtio_gpu_resp_cb ;
struct virtio_gpu_vbuffer {scalar_t__ buf; } ;
struct virtio_gpu_device {int dummy; } ;
typedef  void virtio_gpu_command ;

/* Variables and functions */
 void* ERR_CAST (struct virtio_gpu_vbuffer*) ; 
 scalar_t__ IS_ERR (struct virtio_gpu_vbuffer*) ; 
 struct virtio_gpu_vbuffer* virtio_gpu_get_vbuf (struct virtio_gpu_device*,int,int,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *virtio_gpu_alloc_cmd_resp(struct virtio_gpu_device *vgdev,
				       virtio_gpu_resp_cb cb,
				       struct virtio_gpu_vbuffer **vbuffer_p,
				       int cmd_size, int resp_size,
				       void *resp_buf)
{
	struct virtio_gpu_vbuffer *vbuf;

	vbuf = virtio_gpu_get_vbuf(vgdev, cmd_size,
				   resp_size, resp_buf, cb);
	if (IS_ERR(vbuf)) {
		*vbuffer_p = NULL;
		return ERR_CAST(vbuf);
	}
	*vbuffer_p = vbuf;
	return (struct virtio_gpu_command *)vbuf->buf;
}