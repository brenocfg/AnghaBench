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

/* Variables and functions */
#define  DRM_FORMAT_ARGB8888 131 
#define  DRM_FORMAT_BGRA8888 130 
#define  DRM_FORMAT_BGRX8888 129 
#define  DRM_FORMAT_XRGB8888 128 
 int VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM ; 
 int VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM ; 
 int VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM ; 
 int VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

uint32_t virtio_gpu_translate_format(uint32_t drm_fourcc)
{
	uint32_t format;

	switch (drm_fourcc) {
	case DRM_FORMAT_XRGB8888:
		format = VIRTIO_GPU_FORMAT_B8G8R8X8_UNORM;
		break;
	case DRM_FORMAT_ARGB8888:
		format = VIRTIO_GPU_FORMAT_B8G8R8A8_UNORM;
		break;
	case DRM_FORMAT_BGRX8888:
		format = VIRTIO_GPU_FORMAT_X8R8G8B8_UNORM;
		break;
	case DRM_FORMAT_BGRA8888:
		format = VIRTIO_GPU_FORMAT_A8R8G8B8_UNORM;
		break;
	default:
		/*
		 * This should not happen, we handle everything listed
		 * in virtio_gpu_formats[].
		 */
		format = 0;
		break;
	}
	WARN_ON(format == 0);
	return format;
}