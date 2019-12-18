#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int x1; int x2; int y1; int y2; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; struct drm_framebuffer* fb; TYPE_1__ rect; } ;
struct gm12u320_device {TYPE_3__ fb_update; scalar_t__* data_buf; } ;
struct drm_framebuffer {int* pitches; TYPE_4__** obj; } ;
struct TYPE_9__ {TYPE_2__* import_attach; } ;
struct TYPE_7__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int DATA_BLOCK_CONTENT_SIZE ; 
 int DATA_BLOCK_HEADER_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  GM12U320_ERR (char*,int) ; 
 int GM12U320_REAL_WIDTH ; 
 int GM12U320_USER_WIDTH ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int dma_buf_begin_cpu_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_buf_end_cpu_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 void* drm_gem_shmem_vmap (TYPE_4__*) ; 
 int /*<<< orphan*/  drm_gem_shmem_vunmap (TYPE_4__*,void*) ; 
 int /*<<< orphan*/  gm12u320_32bpp_to_24bpp_packed (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gm12u320_copy_fb_to_blocks(struct gm12u320_device *gm12u320)
{
	int block, dst_offset, len, remain, ret, x1, x2, y1, y2;
	struct drm_framebuffer *fb;
	void *vaddr;
	u8 *src;

	mutex_lock(&gm12u320->fb_update.lock);

	if (!gm12u320->fb_update.fb)
		goto unlock;

	fb = gm12u320->fb_update.fb;
	x1 = gm12u320->fb_update.rect.x1;
	x2 = gm12u320->fb_update.rect.x2;
	y1 = gm12u320->fb_update.rect.y1;
	y2 = gm12u320->fb_update.rect.y2;

	vaddr = drm_gem_shmem_vmap(fb->obj[0]);
	if (IS_ERR(vaddr)) {
		GM12U320_ERR("failed to vmap fb: %ld\n", PTR_ERR(vaddr));
		goto put_fb;
	}

	if (fb->obj[0]->import_attach) {
		ret = dma_buf_begin_cpu_access(
			fb->obj[0]->import_attach->dmabuf, DMA_FROM_DEVICE);
		if (ret) {
			GM12U320_ERR("dma_buf_begin_cpu_access err: %d\n", ret);
			goto vunmap;
		}
	}

	src = vaddr + y1 * fb->pitches[0] + x1 * 4;

	x1 += (GM12U320_REAL_WIDTH - GM12U320_USER_WIDTH) / 2;
	x2 += (GM12U320_REAL_WIDTH - GM12U320_USER_WIDTH) / 2;

	for (; y1 < y2; y1++) {
		remain = 0;
		len = (x2 - x1) * 3;
		dst_offset = (y1 * GM12U320_REAL_WIDTH + x1) * 3;
		block = dst_offset / DATA_BLOCK_CONTENT_SIZE;
		dst_offset %= DATA_BLOCK_CONTENT_SIZE;

		if ((dst_offset + len) > DATA_BLOCK_CONTENT_SIZE) {
			remain = dst_offset + len - DATA_BLOCK_CONTENT_SIZE;
			len = DATA_BLOCK_CONTENT_SIZE - dst_offset;
		}

		dst_offset += DATA_BLOCK_HEADER_SIZE;
		len /= 3;

		gm12u320_32bpp_to_24bpp_packed(
			gm12u320->data_buf[block] + dst_offset,
			src, len);

		if (remain) {
			block++;
			dst_offset = DATA_BLOCK_HEADER_SIZE;
			gm12u320_32bpp_to_24bpp_packed(
				gm12u320->data_buf[block] + dst_offset,
				src + len * 4, remain / 3);
		}
		src += fb->pitches[0];
	}

	if (fb->obj[0]->import_attach) {
		ret = dma_buf_end_cpu_access(fb->obj[0]->import_attach->dmabuf,
					     DMA_FROM_DEVICE);
		if (ret)
			GM12U320_ERR("dma_buf_end_cpu_access err: %d\n", ret);
	}
vunmap:
	drm_gem_shmem_vunmap(fb->obj[0], vaddr);
put_fb:
	drm_framebuffer_put(fb);
	gm12u320->fb_update.fb = NULL;
unlock:
	mutex_unlock(&gm12u320->fb_update.lock);
}