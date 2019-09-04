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
struct virtio_gpu_box {void* d; void* h; void* w; void* z; void* y; void* x; } ;
struct drm_virtgpu_3d_box {int /*<<< orphan*/  d; int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void convert_to_hw_box(struct virtio_gpu_box *dst,
			      const struct drm_virtgpu_3d_box *src)
{
	dst->x = cpu_to_le32(src->x);
	dst->y = cpu_to_le32(src->y);
	dst->z = cpu_to_le32(src->z);
	dst->w = cpu_to_le32(src->w);
	dst->h = cpu_to_le32(src->h);
	dst->d = cpu_to_le32(src->d);
}