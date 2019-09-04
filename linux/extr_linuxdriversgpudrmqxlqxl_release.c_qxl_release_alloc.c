#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ seqno; int /*<<< orphan*/ * ops; } ;
struct qxl_release {int type; int id; TYPE_1__ base; int /*<<< orphan*/  bos; scalar_t__ surface_release_id; scalar_t__ release_offset; } ;
struct qxl_device {int /*<<< orphan*/  release_idr_lock; scalar_t__ release_seqno; int /*<<< orphan*/  release_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct qxl_release*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  kfree (struct qxl_release*) ; 
 struct qxl_release* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qxl_release_alloc(struct qxl_device *qdev, int type,
		  struct qxl_release **ret)
{
	struct qxl_release *release;
	int handle;
	size_t size = sizeof(*release);

	release = kmalloc(size, GFP_KERNEL);
	if (!release) {
		DRM_ERROR("Out of memory\n");
		return -ENOMEM;
	}
	release->base.ops = NULL;
	release->type = type;
	release->release_offset = 0;
	release->surface_release_id = 0;
	INIT_LIST_HEAD(&release->bos);

	idr_preload(GFP_KERNEL);
	spin_lock(&qdev->release_idr_lock);
	handle = idr_alloc(&qdev->release_idr, release, 1, 0, GFP_NOWAIT);
	release->base.seqno = ++qdev->release_seqno;
	spin_unlock(&qdev->release_idr_lock);
	idr_preload_end();
	if (handle < 0) {
		kfree(release);
		*ret = NULL;
		return handle;
	}
	*ret = release;
	DRM_DEBUG_DRIVER("allocated release %d\n", handle);
	release->id = handle;
	return handle;
}