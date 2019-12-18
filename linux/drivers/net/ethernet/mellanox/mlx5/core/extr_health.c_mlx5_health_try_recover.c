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
struct mlx5_core_dev {int /*<<< orphan*/  intf_state; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  MLX5_RECOVERY_WAIT_MSECS ; 
 scalar_t__ check_fatal_sensors (struct mlx5_core_dev*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int /*<<< orphan*/  mlx5_handle_bad_state (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_recover_device (struct mlx5_core_dev*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ sensor_pci_not_working (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mlx5_health_try_recover(struct mlx5_core_dev *dev)
{
	unsigned long end;

	mlx5_core_warn(dev, "handling bad device here\n");
	mlx5_handle_bad_state(dev);
	end = jiffies + msecs_to_jiffies(MLX5_RECOVERY_WAIT_MSECS);
	while (sensor_pci_not_working(dev)) {
		if (time_after(jiffies, end)) {
			mlx5_core_err(dev,
				      "health recovery flow aborted, PCI reads still not working\n");
			return -EIO;
		}
		msleep(100);
	}

	mlx5_core_err(dev, "starting health recovery flow\n");
	mlx5_recover_device(dev);
	if (!test_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state) ||
	    check_fatal_sensors(dev)) {
		mlx5_core_err(dev, "health recovery failed\n");
		return -EIO;
	}
	return 0;
}