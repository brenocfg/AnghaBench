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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_cq {int /*<<< orphan*/  wq; } ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u32_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u64_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cqwq_get_log_stride_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_cqwq_get_size (int /*<<< orphan*/ *) ; 
 int mlx5e_reporter_named_obj_nest_end (struct devlink_fmsg*) ; 
 int mlx5e_reporter_named_obj_nest_start (struct devlink_fmsg*,char*) ; 

int mlx5e_reporter_cq_common_diagnose(struct mlx5e_cq *cq, struct devlink_fmsg *fmsg)
{
	u8 cq_log_stride;
	u32 cq_sz;
	int err;

	cq_sz = mlx5_cqwq_get_size(&cq->wq);
	cq_log_stride = mlx5_cqwq_get_log_stride_size(&cq->wq);

	err = mlx5e_reporter_named_obj_nest_start(fmsg, "CQ");
	if (err)
		return err;

	err = devlink_fmsg_u64_pair_put(fmsg, "stride size", BIT(cq_log_stride));
	if (err)
		return err;

	err = devlink_fmsg_u32_pair_put(fmsg, "size", cq_sz);
	if (err)
		return err;

	err = mlx5e_reporter_named_obj_nest_end(fmsg);
	if (err)
		return err;

	return 0;
}