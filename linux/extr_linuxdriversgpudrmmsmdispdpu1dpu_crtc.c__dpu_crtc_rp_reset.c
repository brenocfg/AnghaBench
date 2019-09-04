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
struct mutex {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  put; int /*<<< orphan*/  get; } ;
struct dpu_crtc_respool {struct list_head* rp_head; int /*<<< orphan*/  rp_list; TYPE_1__ ops; int /*<<< orphan*/  res_list; scalar_t__ sequence_id; struct mutex* rp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dpu_crtc_hw_blk_get ; 
 int /*<<< orphan*/  _dpu_crtc_hw_blk_put ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (struct mutex*) ; 
 int /*<<< orphan*/  mutex_unlock (struct mutex*) ; 

__attribute__((used)) static void _dpu_crtc_rp_reset(struct dpu_crtc_respool *rp,
		struct mutex *rp_lock, struct list_head *rp_head)
{
	if (!rp || !rp_lock || !rp_head) {
		DPU_ERROR("invalid resource pool\n");
		return;
	}

	mutex_lock(rp_lock);
	rp->rp_lock = rp_lock;
	rp->rp_head = rp_head;
	INIT_LIST_HEAD(&rp->rp_list);
	rp->sequence_id = 0;
	INIT_LIST_HEAD(&rp->res_list);
	rp->ops.get = _dpu_crtc_hw_blk_get;
	rp->ops.put = _dpu_crtc_hw_blk_put;
	list_add_tail(&rp->rp_list, rp->rp_head);
	mutex_unlock(rp_lock);
}