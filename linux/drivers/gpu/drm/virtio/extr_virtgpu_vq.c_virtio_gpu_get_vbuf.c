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
struct virtio_gpu_vbuffer {int size; int resp_size; void* resp_buf; void* buf; int /*<<< orphan*/  resp_cb; } ;
struct virtio_gpu_device {int /*<<< orphan*/  vbufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct virtio_gpu_vbuffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_INLINE_CMD_SIZE ; 
 int MAX_INLINE_RESP_SIZE ; 
 struct virtio_gpu_vbuffer* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct virtio_gpu_vbuffer*
virtio_gpu_get_vbuf(struct virtio_gpu_device *vgdev,
		    int size, int resp_size, void *resp_buf,
		    virtio_gpu_resp_cb resp_cb)
{
	struct virtio_gpu_vbuffer *vbuf;

	vbuf = kmem_cache_zalloc(vgdev->vbufs, GFP_KERNEL);
	if (!vbuf)
		return ERR_PTR(-ENOMEM);

	BUG_ON(size > MAX_INLINE_CMD_SIZE);
	vbuf->buf = (void *)vbuf + sizeof(*vbuf);
	vbuf->size = size;

	vbuf->resp_cb = resp_cb;
	vbuf->resp_size = resp_size;
	if (resp_size <= MAX_INLINE_RESP_SIZE)
		vbuf->resp_buf = (void *)vbuf->buf + size;
	else
		vbuf->resp_buf = resp_buf;
	BUG_ON(!vbuf->resp_buf);
	return vbuf;
}