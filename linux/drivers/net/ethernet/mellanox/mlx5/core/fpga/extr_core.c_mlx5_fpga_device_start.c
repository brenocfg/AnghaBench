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
typedef  void* u32 ;
struct mlx5_fpga_device {scalar_t__ last_oper_image; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  state; int /*<<< orphan*/  fpga_qp_err_nb; struct mlx5_core_dev* mdev; int /*<<< orphan*/  fpga_err_nb; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_num_qps; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  FPGA_ERROR ; 
 int /*<<< orphan*/  FPGA_QP_ERROR ; 
 void* MLX5_CAP_FPGA (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_FPGA_IMAGE_USER ; 
 int /*<<< orphan*/  MLX5_FPGA_STATUS_FAILURE ; 
 int /*<<< orphan*/  MLX5_FPGA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  MLX5_NB_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_device ; 
 int /*<<< orphan*/  fpga_err_event ; 
 int /*<<< orphan*/  fpga_qp_err_event ; 
 int /*<<< orphan*/  ieee_vendor_id ; 
 int /*<<< orphan*/  image_version ; 
 int mlx5_core_reserve_gids (struct mlx5_core_dev*,unsigned int) ; 
 int /*<<< orphan*/  mlx5_core_unreserve_gids (struct mlx5_core_dev*,unsigned int) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_register (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_eq_notifier_unregister (struct mlx5_core_dev*,int /*<<< orphan*/ *) ; 
 int mlx5_fpga_caps (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_device_cleanup (struct mlx5_fpga_device*) ; 
 int mlx5_fpga_conn_device_init (struct mlx5_fpga_device*) ; 
 int mlx5_fpga_device_brb (struct mlx5_fpga_device*) ; 
 int mlx5_fpga_device_load_check (struct mlx5_fpga_device*) ; 
 int /*<<< orphan*/  mlx5_fpga_device_name (void*) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*) ; 
 int /*<<< orphan*/  mlx5_fpga_image_name (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_fpga_info (struct mlx5_fpga_device*,char*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,void*,void*,void*) ; 
 int /*<<< orphan*/  sandbox_product_id ; 
 int /*<<< orphan*/  sandbox_product_version ; 
 TYPE_1__ shell_caps ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mlx5_fpga_device_start(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;
	unsigned int max_num_qps;
	unsigned long flags;
	u32 fpga_device_id;
	int err;

	if (!fdev)
		return 0;

	err = mlx5_fpga_device_load_check(fdev);
	if (err)
		goto out;

	err = mlx5_fpga_caps(fdev->mdev);
	if (err)
		goto out;

	fpga_device_id = MLX5_CAP_FPGA(fdev->mdev, fpga_device);
	mlx5_fpga_info(fdev, "%s:%u; %s image, version %u; SBU %06x:%04x version %d\n",
		       mlx5_fpga_device_name(fpga_device_id),
		       fpga_device_id,
		       mlx5_fpga_image_name(fdev->last_oper_image),
		       MLX5_CAP_FPGA(fdev->mdev, image_version),
		       MLX5_CAP_FPGA(fdev->mdev, ieee_vendor_id),
		       MLX5_CAP_FPGA(fdev->mdev, sandbox_product_id),
		       MLX5_CAP_FPGA(fdev->mdev, sandbox_product_version));

	max_num_qps = MLX5_CAP_FPGA(mdev, shell_caps.max_num_qps);
	if (!max_num_qps) {
		mlx5_fpga_err(fdev, "FPGA reports 0 QPs in SHELL_CAPS\n");
		err = -ENOTSUPP;
		goto out;
	}

	err = mlx5_core_reserve_gids(mdev, max_num_qps);
	if (err)
		goto out;

	MLX5_NB_INIT(&fdev->fpga_err_nb, fpga_err_event, FPGA_ERROR);
	MLX5_NB_INIT(&fdev->fpga_qp_err_nb, fpga_qp_err_event, FPGA_QP_ERROR);
	mlx5_eq_notifier_register(fdev->mdev, &fdev->fpga_err_nb);
	mlx5_eq_notifier_register(fdev->mdev, &fdev->fpga_qp_err_nb);

	err = mlx5_fpga_conn_device_init(fdev);
	if (err)
		goto err_rsvd_gid;

	if (fdev->last_oper_image == MLX5_FPGA_IMAGE_USER) {
		err = mlx5_fpga_device_brb(fdev);
		if (err)
			goto err_conn_init;
	}

	goto out;

err_conn_init:
	mlx5_fpga_conn_device_cleanup(fdev);

err_rsvd_gid:
	mlx5_eq_notifier_unregister(fdev->mdev, &fdev->fpga_err_nb);
	mlx5_eq_notifier_unregister(fdev->mdev, &fdev->fpga_qp_err_nb);
	mlx5_core_unreserve_gids(mdev, max_num_qps);
out:
	spin_lock_irqsave(&fdev->state_lock, flags);
	fdev->state = err ? MLX5_FPGA_STATUS_FAILURE : MLX5_FPGA_STATUS_SUCCESS;
	spin_unlock_irqrestore(&fdev->state_lock, flags);
	return err;
}