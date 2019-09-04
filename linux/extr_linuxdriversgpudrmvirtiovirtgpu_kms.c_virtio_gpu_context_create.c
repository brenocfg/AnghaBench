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
struct virtio_gpu_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_gpu_cmd_context_create (struct virtio_gpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  virtio_gpu_ctx_id_get (struct virtio_gpu_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void virtio_gpu_context_create(struct virtio_gpu_device *vgdev,
				      uint32_t nlen, const char *name,
				      uint32_t *ctx_id)
{
	virtio_gpu_ctx_id_get(vgdev, ctx_id);
	virtio_gpu_cmd_context_create(vgdev, *ctx_id, nlen, name);
}