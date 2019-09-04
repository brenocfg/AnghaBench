#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct dma_buf_attachment* import_attach; } ;
struct drm_gem_cma_object {void* vaddr; TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_3__* format; TYPE_2__* dev; } ;
struct drm_format_name_buf {int dummy; } ;
struct drm_clip_rect {int dummy; } ;
struct dma_buf_attachment {int /*<<< orphan*/  dmabuf; } ;
struct TYPE_6__ {int format; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
#define  DRM_FORMAT_RGB565 129 
#define  DRM_FORMAT_XRGB8888 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err_once (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int dma_buf_begin_cpu_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_buf_end_cpu_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_get_format_name (int,struct drm_format_name_buf*) ; 
 int /*<<< orphan*/  tinydrm_memcpy (void*,void*,struct drm_framebuffer*,struct drm_clip_rect*) ; 
 int /*<<< orphan*/  tinydrm_swab16 (void*,void*,struct drm_framebuffer*,struct drm_clip_rect*) ; 
 int /*<<< orphan*/  tinydrm_xrgb8888_to_rgb565 (void*,void*,struct drm_framebuffer*,struct drm_clip_rect*,int) ; 

int mipi_dbi_buf_copy(void *dst, struct drm_framebuffer *fb,
		      struct drm_clip_rect *clip, bool swap)
{
	struct drm_gem_cma_object *cma_obj = drm_fb_cma_get_gem_obj(fb, 0);
	struct dma_buf_attachment *import_attach = cma_obj->base.import_attach;
	struct drm_format_name_buf format_name;
	void *src = cma_obj->vaddr;
	int ret = 0;

	if (import_attach) {
		ret = dma_buf_begin_cpu_access(import_attach->dmabuf,
					       DMA_FROM_DEVICE);
		if (ret)
			return ret;
	}

	switch (fb->format->format) {
	case DRM_FORMAT_RGB565:
		if (swap)
			tinydrm_swab16(dst, src, fb, clip);
		else
			tinydrm_memcpy(dst, src, fb, clip);
		break;
	case DRM_FORMAT_XRGB8888:
		tinydrm_xrgb8888_to_rgb565(dst, src, fb, clip, swap);
		break;
	default:
		dev_err_once(fb->dev->dev, "Format is not supported: %s\n",
			     drm_get_format_name(fb->format->format,
						 &format_name));
		return -EINVAL;
	}

	if (import_attach)
		ret = dma_buf_end_cpu_access(import_attach->dmabuf,
					     DMA_FROM_DEVICE);
	return ret;
}