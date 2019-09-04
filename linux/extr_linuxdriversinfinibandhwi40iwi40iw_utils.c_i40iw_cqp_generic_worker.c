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
struct work_struct {int dummy; } ;
struct i40iw_virtchnl_work_info {scalar_t__ worker_vf_dev; int /*<<< orphan*/  (* callback_fcn ) (scalar_t__) ;} ;
struct virtchnl_work {struct i40iw_virtchnl_work_info work_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void i40iw_cqp_generic_worker(struct work_struct *work)
{
	struct i40iw_virtchnl_work_info *work_info =
	    &((struct virtchnl_work *)work)->work_info;

	if (work_info->worker_vf_dev)
		work_info->callback_fcn(work_info->worker_vf_dev);
}