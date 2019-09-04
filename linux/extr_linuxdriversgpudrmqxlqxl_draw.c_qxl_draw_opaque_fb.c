#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct qxl_release {int dummy; } ;
struct qxl_rect {int left; int right; int top; int bottom; } ;
struct TYPE_8__ {void* palette; } ;
struct TYPE_9__ {TYPE_1__ bitmap; } ;
struct qxl_image {TYPE_2__ u; } ;
struct fb_image {int dx; int dy; int width; int height; char* data; int depth; } ;
struct qxl_fb_image {struct fb_image fb_image; struct qxl_device* qdev; } ;
struct qxl_drm_image {struct qxl_bo* bo; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_12__ {scalar_t__ bitmap; TYPE_4__ pos; scalar_t__ flags; } ;
struct TYPE_10__ {int bottom; int right; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_13__ {void* src_bitmap; TYPE_5__ mask; scalar_t__ scale_mode; int /*<<< orphan*/  rop_descriptor; TYPE_3__ src_area; } ;
struct TYPE_14__ {TYPE_6__ copy; } ;
struct qxl_drawable {int /*<<< orphan*/  release_info; TYPE_7__ u; } ;
struct qxl_device {int dummy; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QXL_CMD_DRAW ; 
 int /*<<< orphan*/  QXL_DRAW_COPY ; 
 int /*<<< orphan*/  SPICE_ROPD_OP_PUT ; 
 int alloc_drawable (struct qxl_device*,struct qxl_release**) ; 
 int alloc_palette_object (struct qxl_device*,struct qxl_release*,struct qxl_bo**) ; 
 int /*<<< orphan*/  free_drawable (struct qxl_device*,struct qxl_release*) ; 
 int make_drawable (struct qxl_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qxl_rect*,struct qxl_release*) ; 
 void* qxl_bo_kmap_atomic_page (struct qxl_device*,struct qxl_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_bo_kunmap_atomic_page (struct qxl_device*,struct qxl_bo*,void*) ; 
 void* qxl_bo_physical_address (struct qxl_device*,struct qxl_bo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qxl_bo_unref (struct qxl_bo**) ; 
 int qxl_image_alloc_objects (struct qxl_device*,struct qxl_release*,struct qxl_drm_image**,int,int) ; 
 int /*<<< orphan*/  qxl_image_free_objects (struct qxl_device*,struct qxl_drm_image*) ; 
 int qxl_image_init (struct qxl_device*,struct qxl_release*,struct qxl_drm_image*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int qxl_palette_create_1bit (struct qxl_bo*,struct qxl_release*,struct qxl_fb_image const*) ; 
 int /*<<< orphan*/  qxl_push_command_ring_release (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qxl_release_backoff_reserve_list (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_fence_buffer_objects (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_release_free (struct qxl_device*,struct qxl_release*) ; 
 scalar_t__ qxl_release_map (struct qxl_device*,struct qxl_release*) ; 
 int qxl_release_reserve_list (struct qxl_release*,int) ; 
 int /*<<< orphan*/  qxl_release_unmap (struct qxl_device*,struct qxl_release*,int /*<<< orphan*/ *) ; 

void qxl_draw_opaque_fb(const struct qxl_fb_image *qxl_fb_image,
			int stride /* filled in if 0 */)
{
	struct qxl_device *qdev = qxl_fb_image->qdev;
	struct qxl_drawable *drawable;
	struct qxl_rect rect;
	const struct fb_image *fb_image = &qxl_fb_image->fb_image;
	int x = fb_image->dx;
	int y = fb_image->dy;
	int width = fb_image->width;
	int height = fb_image->height;
	const char *src = fb_image->data;
	int depth = fb_image->depth;
	struct qxl_release *release;
	struct qxl_image *image;
	int ret;
	struct qxl_drm_image *dimage;
	struct qxl_bo *palette_bo = NULL;
	if (stride == 0)
		stride = depth * width / 8;

	ret = alloc_drawable(qdev, &release);
	if (ret)
		return;

	ret = qxl_image_alloc_objects(qdev, release,
				      &dimage,
				      height, stride);
	if (ret)
		goto out_free_drawable;

	if (depth == 1) {
		ret = alloc_palette_object(qdev, release, &palette_bo);
		if (ret)
			goto out_free_image;
	}

	/* do a reservation run over all the objects we just allocated */
	ret = qxl_release_reserve_list(release, true);
	if (ret)
		goto out_free_palette;

	rect.left = x;
	rect.right = x + width;
	rect.top = y;
	rect.bottom = y + height;

	ret = make_drawable(qdev, 0, QXL_DRAW_COPY, &rect, release);
	if (ret) {
		qxl_release_backoff_reserve_list(release);
		goto out_free_palette;
	}

	ret = qxl_image_init(qdev, release, dimage,
			     (const uint8_t *)src, 0, 0,
			     width, height, depth, stride);
	if (ret) {
		qxl_release_backoff_reserve_list(release);
		qxl_release_free(qdev, release);
		return;
	}

	if (depth == 1) {
		void *ptr;
		ret = qxl_palette_create_1bit(palette_bo, release, qxl_fb_image);

		ptr = qxl_bo_kmap_atomic_page(qdev, dimage->bo, 0);
		image = ptr;
		image->u.bitmap.palette =
			qxl_bo_physical_address(qdev, palette_bo, 0);
		qxl_bo_kunmap_atomic_page(qdev, dimage->bo, ptr);
	}

	drawable = (struct qxl_drawable *)qxl_release_map(qdev, release);

	drawable->u.copy.src_area.top = 0;
	drawable->u.copy.src_area.bottom = height;
	drawable->u.copy.src_area.left = 0;
	drawable->u.copy.src_area.right = width;

	drawable->u.copy.rop_descriptor = SPICE_ROPD_OP_PUT;
	drawable->u.copy.scale_mode = 0;
	drawable->u.copy.mask.flags = 0;
	drawable->u.copy.mask.pos.x = 0;
	drawable->u.copy.mask.pos.y = 0;
	drawable->u.copy.mask.bitmap = 0;

	drawable->u.copy.src_bitmap =
		qxl_bo_physical_address(qdev, dimage->bo, 0);
	qxl_release_unmap(qdev, release, &drawable->release_info);

	qxl_push_command_ring_release(qdev, release, QXL_CMD_DRAW, false);
	qxl_release_fence_buffer_objects(release);

out_free_palette:
	if (palette_bo)
		qxl_bo_unref(&palette_bo);
out_free_image:
	qxl_image_free_objects(qdev, dimage);
out_free_drawable:
	if (ret)
		free_drawable(qdev, release);
}