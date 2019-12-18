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
struct virtio_gpu_vbuffer {scalar_t__ resp_size; int /*<<< orphan*/  data_buf; int /*<<< orphan*/  resp_buf; } ;
struct virtio_gpu_device {int /*<<< orphan*/  vbufs; } ;

/* Variables and functions */
 scalar_t__ MAX_INLINE_RESP_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct virtio_gpu_vbuffer*) ; 

__attribute__((used)) static void free_vbuf(struct virtio_gpu_device *vgdev,
		      struct virtio_gpu_vbuffer *vbuf)
{
	if (vbuf->resp_size > MAX_INLINE_RESP_SIZE)
		kfree(vbuf->resp_buf);
	kfree(vbuf->data_buf);
	kmem_cache_free(vgdev->vbufs, vbuf);
}