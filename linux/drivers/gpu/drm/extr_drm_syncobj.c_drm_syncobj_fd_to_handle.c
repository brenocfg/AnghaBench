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
typedef  int u32 ;
struct fd {TYPE_1__* file; } ;
struct drm_syncobj {int dummy; } ;
struct drm_file {int /*<<< orphan*/  syncobj_table_lock; int /*<<< orphan*/  syncobj_idr; } ;
struct TYPE_2__ {struct drm_syncobj* private_data; int /*<<< orphan*/ * f_op; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  drm_syncobj_file_fops ; 
 int /*<<< orphan*/  drm_syncobj_get (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 struct fd fdget (int) ; 
 int /*<<< orphan*/  fdput (struct fd) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct drm_syncobj*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_syncobj_fd_to_handle(struct drm_file *file_private,
				    int fd, u32 *handle)
{
	struct drm_syncobj *syncobj;
	struct fd f = fdget(fd);
	int ret;

	if (!f.file)
		return -EINVAL;

	if (f.file->f_op != &drm_syncobj_file_fops) {
		fdput(f);
		return -EINVAL;
	}

	/* take a reference to put in the idr */
	syncobj = f.file->private_data;
	drm_syncobj_get(syncobj);

	idr_preload(GFP_KERNEL);
	spin_lock(&file_private->syncobj_table_lock);
	ret = idr_alloc(&file_private->syncobj_idr, syncobj, 1, 0, GFP_NOWAIT);
	spin_unlock(&file_private->syncobj_table_lock);
	idr_preload_end();

	if (ret > 0) {
		*handle = ret;
		ret = 0;
	} else
		drm_syncobj_put(syncobj);

	fdput(f);
	return ret;
}