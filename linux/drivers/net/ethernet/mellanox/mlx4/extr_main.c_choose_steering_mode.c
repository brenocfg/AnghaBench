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
struct mlx4_dev_cap {int flags2; scalar_t__ fs_max_num_qp_per_entry; int /*<<< orphan*/  fs_log_max_ucast_qp_range_size; } ;
struct TYPE_4__ {scalar_t__ dmfs_high_steer_mode; scalar_t__ num_qp_per_mgm; int flags; int /*<<< orphan*/  steering_mode; int /*<<< orphan*/  fs_log_max_ucast_qp_range_size; } ;
struct mlx4_dev {int oper_log_mgm_entry_size; TYPE_2__ caps; TYPE_1__* persist; } ;
struct TYPE_3__ {scalar_t__ num_vfs; } ;

/* Variables and functions */
 int MLX4_DEFAULT_MGM_LOG_ENTRY_SIZE ; 
 int MLX4_DEV_CAP_FLAG2_FS_EN ; 
 int MLX4_DEV_CAP_FLAG_VEP_MC_STEER ; 
 int MLX4_DEV_CAP_FLAG_VEP_UC_STEER ; 
 int MLX4_DMFS_A0_STEERING ; 
 scalar_t__ MLX4_MIN_MGM_LOG_ENTRY_SIZE ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_DISABLE ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_NOT_SUPPORTED ; 
 scalar_t__ MLX4_STEERING_DMFS_A0_STATIC ; 
 int /*<<< orphan*/  MLX4_STEERING_MODE_A0 ; 
 int /*<<< orphan*/  MLX4_STEERING_MODE_B0 ; 
 int /*<<< orphan*/  MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 scalar_t__ choose_log_fs_mgm_entry_size (scalar_t__) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 scalar_t__ mlx4_get_qp_per_mgm (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (struct mlx4_dev*) ; 
 int mlx4_log_num_mgm_entry_size ; 
 int /*<<< orphan*/  mlx4_steering_mode_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 

__attribute__((used)) static void choose_steering_mode(struct mlx4_dev *dev,
				 struct mlx4_dev_cap *dev_cap)
{
	if (mlx4_log_num_mgm_entry_size <= 0) {
		if ((-mlx4_log_num_mgm_entry_size) & MLX4_DMFS_A0_STEERING) {
			if (dev->caps.dmfs_high_steer_mode ==
			    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
				mlx4_err(dev, "DMFS high rate mode not supported\n");
			else
				dev->caps.dmfs_high_steer_mode =
					MLX4_STEERING_DMFS_A0_STATIC;
		}
	}

	if (mlx4_log_num_mgm_entry_size <= 0 &&
	    dev_cap->flags2 & MLX4_DEV_CAP_FLAG2_FS_EN &&
	    (!mlx4_is_mfunc(dev) ||
	     (dev_cap->fs_max_num_qp_per_entry >=
	     (dev->persist->num_vfs + 1))) &&
	    choose_log_fs_mgm_entry_size(dev_cap->fs_max_num_qp_per_entry) >=
		MLX4_MIN_MGM_LOG_ENTRY_SIZE) {
		dev->oper_log_mgm_entry_size =
			choose_log_fs_mgm_entry_size(dev_cap->fs_max_num_qp_per_entry);
		dev->caps.steering_mode = MLX4_STEERING_MODE_DEVICE_MANAGED;
		dev->caps.num_qp_per_mgm = dev_cap->fs_max_num_qp_per_entry;
		dev->caps.fs_log_max_ucast_qp_range_size =
			dev_cap->fs_log_max_ucast_qp_range_size;
	} else {
		if (dev->caps.dmfs_high_steer_mode !=
		    MLX4_STEERING_DMFS_A0_NOT_SUPPORTED)
			dev->caps.dmfs_high_steer_mode = MLX4_STEERING_DMFS_A0_DISABLE;
		if (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_UC_STEER &&
		    dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER)
			dev->caps.steering_mode = MLX4_STEERING_MODE_B0;
		else {
			dev->caps.steering_mode = MLX4_STEERING_MODE_A0;

			if (dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_UC_STEER ||
			    dev->caps.flags & MLX4_DEV_CAP_FLAG_VEP_MC_STEER)
				mlx4_warn(dev, "Must have both UC_STEER and MC_STEER flags set to use B0 steering - falling back to A0 steering mode\n");
		}
		dev->oper_log_mgm_entry_size =
			mlx4_log_num_mgm_entry_size > 0 ?
			mlx4_log_num_mgm_entry_size :
			MLX4_DEFAULT_MGM_LOG_ENTRY_SIZE;
		dev->caps.num_qp_per_mgm = mlx4_get_qp_per_mgm(dev);
	}
	mlx4_dbg(dev, "Steering mode is: %s, oper_log_mgm_entry_size = %d, modparam log_num_mgm_entry_size = %d\n",
		 mlx4_steering_mode_str(dev->caps.steering_mode),
		 dev->oper_log_mgm_entry_size,
		 mlx4_log_num_mgm_entry_size);
}