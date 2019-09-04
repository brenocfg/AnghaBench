#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ops; } ;
struct qxl_release {TYPE_1__ base; int /*<<< orphan*/  bos; int /*<<< orphan*/  id; scalar_t__ surface_release_id; int /*<<< orphan*/  type; } ;
struct qxl_device {int /*<<< orphan*/  release_idr_lock; int /*<<< orphan*/  release_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (TYPE_1__*) ; 
 int /*<<< orphan*/  dma_fence_signal (TYPE_1__*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qxl_release*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_release_free_list (struct qxl_release*) ; 
 int /*<<< orphan*/  qxl_surface_id_dealloc (struct qxl_device*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
qxl_release_free(struct qxl_device *qdev,
		 struct qxl_release *release)
{
	DRM_DEBUG_DRIVER("release %d, type %d\n", release->id, release->type);

	if (release->surface_release_id)
		qxl_surface_id_dealloc(qdev, release->surface_release_id);

	spin_lock(&qdev->release_idr_lock);
	idr_remove(&qdev->release_idr, release->id);
	spin_unlock(&qdev->release_idr_lock);

	if (release->base.ops) {
		WARN_ON(list_empty(&release->bos));
		qxl_release_free_list(release);

		dma_fence_signal(&release->base);
		dma_fence_put(&release->base);
	} else {
		qxl_release_free_list(release);
		kfree(release);
	}
}