#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mlx5_fw_reporter_ctx {int dummy; } ;
struct TYPE_3__ {scalar_t__ crdump_size; } ;
struct TYPE_4__ {TYPE_1__ health; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct devlink_health_reporter {int dummy; } ;
struct devlink_fmsg {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MLX5_CR_DUMP_CHUNK_SIZE ; 
 int devlink_fmsg_arr_pair_nest_end (struct devlink_fmsg*) ; 
 int devlink_fmsg_arr_pair_nest_start (struct devlink_fmsg*,char*) ; 
 int devlink_fmsg_binary_put (struct devlink_fmsg*,char*,scalar_t__) ; 
 struct mlx5_core_dev* devlink_health_reporter_priv (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  kvfree (scalar_t__*) ; 
 scalar_t__* kvmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int mlx5_crdump_collect (struct mlx5_core_dev*,scalar_t__*) ; 
 int mlx5_fw_reporter_ctx_pairs_put (struct devlink_fmsg*,struct mlx5_fw_reporter_ctx*) ; 

__attribute__((used)) static int
mlx5_fw_fatal_reporter_dump(struct devlink_health_reporter *reporter,
			    struct devlink_fmsg *fmsg, void *priv_ctx)
{
	struct mlx5_core_dev *dev = devlink_health_reporter_priv(reporter);
	u32 crdump_size = dev->priv.health.crdump_size;
	u32 *cr_data;
	u32 data_size;
	u32 offset;
	int err;

	if (!mlx5_core_is_pf(dev))
		return -EPERM;

	cr_data = kvmalloc(crdump_size, GFP_KERNEL);
	if (!cr_data)
		return -ENOMEM;
	err = mlx5_crdump_collect(dev, cr_data);
	if (err)
		goto free_data;

	if (priv_ctx) {
		struct mlx5_fw_reporter_ctx *fw_reporter_ctx = priv_ctx;

		err = mlx5_fw_reporter_ctx_pairs_put(fmsg, fw_reporter_ctx);
		if (err)
			goto free_data;
	}

	err = devlink_fmsg_arr_pair_nest_start(fmsg, "crdump_data");
	if (err)
		goto free_data;
	for (offset = 0; offset < crdump_size; offset += data_size) {
		if (crdump_size - offset < MLX5_CR_DUMP_CHUNK_SIZE)
			data_size = crdump_size - offset;
		else
			data_size = MLX5_CR_DUMP_CHUNK_SIZE;
		err = devlink_fmsg_binary_put(fmsg, (char *)cr_data + offset,
					      data_size);
		if (err)
			goto free_data;
	}
	err = devlink_fmsg_arr_pair_nest_end(fmsg);

free_data:
	kvfree(cr_data);
	return err;
}