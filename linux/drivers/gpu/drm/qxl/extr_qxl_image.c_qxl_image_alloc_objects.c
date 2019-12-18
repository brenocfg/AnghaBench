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
struct qxl_release {int dummy; } ;
struct qxl_image {int dummy; } ;
struct qxl_drm_image {int /*<<< orphan*/  bo; int /*<<< orphan*/  chunk_list; } ;
struct qxl_device {int dummy; } ;
struct qxl_data_chunk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct qxl_drm_image*) ; 
 struct qxl_drm_image* kmalloc (int,int /*<<< orphan*/ ) ; 
 int qxl_alloc_bo_reserved (struct qxl_device*,struct qxl_release*,int,int /*<<< orphan*/ *) ; 
 int qxl_allocate_chunk (struct qxl_device*,struct qxl_release*,struct qxl_drm_image*,int) ; 
 int /*<<< orphan*/  qxl_bo_unref (int /*<<< orphan*/ *) ; 

int
qxl_image_alloc_objects(struct qxl_device *qdev,
			struct qxl_release *release,
			struct qxl_drm_image **image_ptr,
			int height, int stride)
{
	struct qxl_drm_image *image;
	int ret;

	image = kmalloc(sizeof(struct qxl_drm_image), GFP_KERNEL);
	if (!image)
		return -ENOMEM;

	INIT_LIST_HEAD(&image->chunk_list);

	ret = qxl_alloc_bo_reserved(qdev, release, sizeof(struct qxl_image), &image->bo);
	if (ret) {
		kfree(image);
		return ret;
	}

	ret = qxl_allocate_chunk(qdev, release, image, sizeof(struct qxl_data_chunk) + stride * height);
	if (ret) {
		qxl_bo_unref(&image->bo);
		kfree(image);
		return ret;
	}
	*image_ptr = image;
	return 0;
}