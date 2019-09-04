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
typedef  scalar_t__ uint64_t ;
typedef  size_t uint32_t ;
typedef  int u64 ;
struct msm_gpu_submitqueue {size_t prio; } ;
struct msm_gpu {int /*<<< orphan*/ * rb; } ;
struct msm_gem_submit {int /*<<< orphan*/  ticket; int /*<<< orphan*/  bo_list; int /*<<< orphan*/  node; scalar_t__ nr_cmds; scalar_t__ nr_bos; int /*<<< orphan*/  ring; struct msm_gpu_submitqueue* queue; int /*<<< orphan*/ * bos; void* cmd; int /*<<< orphan*/  pid; int /*<<< orphan*/ * fence; struct msm_gpu* gpu; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ SIZE_MAX ; 
 int __GFP_NORETRY ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_pid (int /*<<< orphan*/ ) ; 
 struct msm_gem_submit* kmalloc (scalar_t__,int) ; 
 int /*<<< orphan*/  reservation_ww_class ; 
 int /*<<< orphan*/  task_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ww_acquire_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct msm_gem_submit *submit_create(struct drm_device *dev,
		struct msm_gpu *gpu, struct msm_gpu_submitqueue *queue,
		uint32_t nr_bos, uint32_t nr_cmds)
{
	struct msm_gem_submit *submit;
	uint64_t sz = sizeof(*submit) + ((u64)nr_bos * sizeof(submit->bos[0])) +
		((u64)nr_cmds * sizeof(submit->cmd[0]));

	if (sz > SIZE_MAX)
		return NULL;

	submit = kmalloc(sz, GFP_KERNEL | __GFP_NOWARN | __GFP_NORETRY);
	if (!submit)
		return NULL;

	submit->dev = dev;
	submit->gpu = gpu;
	submit->fence = NULL;
	submit->pid = get_pid(task_pid(current));
	submit->cmd = (void *)&submit->bos[nr_bos];
	submit->queue = queue;
	submit->ring = gpu->rb[queue->prio];

	/* initially, until copy_from_user() and bo lookup succeeds: */
	submit->nr_bos = 0;
	submit->nr_cmds = 0;

	INIT_LIST_HEAD(&submit->node);
	INIT_LIST_HEAD(&submit->bo_list);
	ww_acquire_init(&submit->ticket, &reservation_ww_class);

	return submit;
}