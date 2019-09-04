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
struct mlx5_core_dev {scalar_t__ state; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  force_teardown ; 
 int mlx5_cmd_force_teardown_hca (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_eq_free_irqs (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_drain_health_wq (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_enter_error_state (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_irq_clear_affinity_hints (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_start_health_poll (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_stop_health_poll (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static int mlx5_try_fast_unload(struct mlx5_core_dev *dev)
{
	int ret;

	if (!MLX5_CAP_GEN(dev, force_teardown)) {
		mlx5_core_dbg(dev, "force teardown is not supported in the firmware\n");
		return -EOPNOTSUPP;
	}

	if (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		mlx5_core_dbg(dev, "Device in internal error state, giving up\n");
		return -EAGAIN;
	}

	/* Panic tear down fw command will stop the PCI bus communication
	 * with the HCA, so the health polll is no longer needed.
	 */
	mlx5_drain_health_wq(dev);
	mlx5_stop_health_poll(dev, false);

	ret = mlx5_cmd_force_teardown_hca(dev);
	if (ret) {
		mlx5_core_dbg(dev, "Firmware couldn't do fast unload error: %d\n", ret);
		mlx5_start_health_poll(dev);
		return ret;
	}

	mlx5_enter_error_state(dev, true);

	/* Some platforms requiring freeing the IRQ's in the shutdown
	 * flow. If they aren't freed they can't be allocated after
	 * kexec. There is no need to cleanup the mlx5_core software
	 * contexts.
	 */
	mlx5_irq_clear_affinity_hints(dev);
	mlx5_core_eq_free_irqs(dev);

	return 0;
}