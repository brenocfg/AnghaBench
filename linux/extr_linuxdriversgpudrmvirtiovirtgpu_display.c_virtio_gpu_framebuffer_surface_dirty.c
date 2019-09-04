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
struct virtio_gpu_framebuffer {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_clip_rect {int dummy; } ;

/* Variables and functions */
 struct virtio_gpu_framebuffer* to_virtio_gpu_framebuffer (struct drm_framebuffer*) ; 
 int virtio_gpu_surface_dirty (struct virtio_gpu_framebuffer*,struct drm_clip_rect*,unsigned int) ; 

__attribute__((used)) static int
virtio_gpu_framebuffer_surface_dirty(struct drm_framebuffer *fb,
				     struct drm_file *file_priv,
				     unsigned int flags, unsigned int color,
				     struct drm_clip_rect *clips,
				     unsigned int num_clips)
{
	struct virtio_gpu_framebuffer *virtio_gpu_fb
		= to_virtio_gpu_framebuffer(fb);

	return virtio_gpu_surface_dirty(virtio_gpu_fb, clips, num_clips);
}