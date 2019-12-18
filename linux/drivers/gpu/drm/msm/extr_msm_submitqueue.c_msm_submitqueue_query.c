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
struct msm_gpu_submitqueue {int dummy; } ;
struct msm_file_private {int dummy; } ;
struct drm_msm_submitqueue_query {scalar_t__ param; int /*<<< orphan*/  id; scalar_t__ pad; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ MSM_SUBMITQUEUE_PARAM_FAULTS ; 
 struct msm_gpu_submitqueue* msm_submitqueue_get (struct msm_file_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_submitqueue_put (struct msm_gpu_submitqueue*) ; 
 int msm_submitqueue_query_faults (struct msm_gpu_submitqueue*,struct drm_msm_submitqueue_query*) ; 

int msm_submitqueue_query(struct drm_device *drm, struct msm_file_private *ctx,
		struct drm_msm_submitqueue_query *args)
{
	struct msm_gpu_submitqueue *queue;
	int ret = -EINVAL;

	if (args->pad)
		return -EINVAL;

	queue = msm_submitqueue_get(ctx, args->id);
	if (!queue)
		return -ENOENT;

	if (args->param == MSM_SUBMITQUEUE_PARAM_FAULTS)
		ret = msm_submitqueue_query_faults(queue, args);

	msm_submitqueue_put(queue);

	return ret;
}