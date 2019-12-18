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
struct mlx5_fw_reporter_ctx {int /*<<< orphan*/  miss_counter; int /*<<< orphan*/  err_synd; } ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int devlink_fmsg_u32_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 
 int devlink_fmsg_u8_pair_put (struct devlink_fmsg*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx5_fw_reporter_ctx_pairs_put(struct devlink_fmsg *fmsg,
			       struct mlx5_fw_reporter_ctx *fw_reporter_ctx)
{
	int err;

	err = devlink_fmsg_u8_pair_put(fmsg, "syndrome",
				       fw_reporter_ctx->err_synd);
	if (err)
		return err;
	err = devlink_fmsg_u32_pair_put(fmsg, "fw_miss_counter",
					fw_reporter_ctx->miss_counter);
	if (err)
		return err;
	return 0;
}