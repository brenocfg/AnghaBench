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
struct qxl_drm_image {int /*<<< orphan*/  chunk_list; } ;
struct qxl_drm_chunk {int /*<<< orphan*/  head; int /*<<< orphan*/  bo; } ;
struct qxl_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct qxl_drm_chunk*) ; 
 struct qxl_drm_chunk* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int qxl_alloc_bo_reserved (struct qxl_device*,struct qxl_release*,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qxl_allocate_chunk(struct qxl_device *qdev,
		   struct qxl_release *release,
		   struct qxl_drm_image *image,
		   unsigned int chunk_size)
{
	struct qxl_drm_chunk *chunk;
	int ret;

	chunk = kmalloc(sizeof(struct qxl_drm_chunk), GFP_KERNEL);
	if (!chunk)
		return -ENOMEM;

	ret = qxl_alloc_bo_reserved(qdev, release, chunk_size, &chunk->bo);
	if (ret) {
		kfree(chunk);
		return ret;
	}

	list_add_tail(&chunk->head, &image->chunk_list);
	return 0;
}