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
typedef  size_t u32 ;
struct virtchnl_work {int /*<<< orphan*/  work; int /*<<< orphan*/  work_info; } ;
struct i40iw_virtchnl_work_info {int dummy; } ;
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_device {int /*<<< orphan*/  virtchnl_wq; struct virtchnl_work* virtchnl_w; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_cqp_generic_worker ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct i40iw_virtchnl_work_info*,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void i40iw_cqp_spawn_worker(struct i40iw_sc_dev *dev,
			    struct i40iw_virtchnl_work_info *work_info,
			    u32 iw_vf_idx)
{
	struct virtchnl_work *work;
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;

	work = &iwdev->virtchnl_w[iw_vf_idx];
	memcpy(&work->work_info, work_info, sizeof(*work_info));
	INIT_WORK(&work->work, i40iw_cqp_generic_worker);
	queue_work(iwdev->virtchnl_wq, &work->work);
}