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
struct panfrost_job {scalar_t__ requirements; int /*<<< orphan*/  render_done_fence; int /*<<< orphan*/  file_priv; int /*<<< orphan*/  flush_id; scalar_t__ jc; struct panfrost_device* pfdev; int /*<<< orphan*/  refcount; } ;
struct panfrost_device {int dummy; } ;
struct drm_syncobj {int dummy; } ;
struct drm_panfrost_submit {scalar_t__ requirements; scalar_t__ out_sync; scalar_t__ jc; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {struct panfrost_device* dev_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PANFROST_JD_REQ_FS ; 
 struct drm_syncobj* drm_syncobj_find (struct drm_file*,scalar_t__) ; 
 int /*<<< orphan*/  drm_syncobj_put (struct drm_syncobj*) ; 
 int /*<<< orphan*/  drm_syncobj_replace_fence (struct drm_syncobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct panfrost_job* kzalloc (int,int /*<<< orphan*/ ) ; 
 int panfrost_copy_in_sync (struct drm_device*,struct drm_file*,struct drm_panfrost_submit*,struct panfrost_job*) ; 
 int /*<<< orphan*/  panfrost_gpu_get_latest_flush_id (struct panfrost_device*) ; 
 int panfrost_job_push (struct panfrost_job*) ; 
 int /*<<< orphan*/  panfrost_job_put (struct panfrost_job*) ; 
 int panfrost_lookup_bos (struct drm_device*,struct drm_file*,struct drm_panfrost_submit*,struct panfrost_job*) ; 

__attribute__((used)) static int panfrost_ioctl_submit(struct drm_device *dev, void *data,
		struct drm_file *file)
{
	struct panfrost_device *pfdev = dev->dev_private;
	struct drm_panfrost_submit *args = data;
	struct drm_syncobj *sync_out = NULL;
	struct panfrost_job *job;
	int ret = 0;

	if (!args->jc)
		return -EINVAL;

	if (args->requirements && args->requirements != PANFROST_JD_REQ_FS)
		return -EINVAL;

	if (args->out_sync > 0) {
		sync_out = drm_syncobj_find(file, args->out_sync);
		if (!sync_out)
			return -ENODEV;
	}

	job = kzalloc(sizeof(*job), GFP_KERNEL);
	if (!job) {
		ret = -ENOMEM;
		goto fail_out_sync;
	}

	kref_init(&job->refcount);

	job->pfdev = pfdev;
	job->jc = args->jc;
	job->requirements = args->requirements;
	job->flush_id = panfrost_gpu_get_latest_flush_id(pfdev);
	job->file_priv = file->driver_priv;

	ret = panfrost_copy_in_sync(dev, file, args, job);
	if (ret)
		goto fail_job;

	ret = panfrost_lookup_bos(dev, file, args, job);
	if (ret)
		goto fail_job;

	ret = panfrost_job_push(job);
	if (ret)
		goto fail_job;

	/* Update the return sync object for the job */
	if (sync_out)
		drm_syncobj_replace_fence(sync_out, job->render_done_fence);

fail_job:
	panfrost_job_put(job);
fail_out_sync:
	if (sync_out)
		drm_syncobj_put(sync_out);

	return ret;
}