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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  FW_INIT_WAIT_MS ; 
 scalar_t__ FW_INIT_WARN_MESSAGE_INTERVAL ; 
 scalar_t__ FW_PRE_INIT_TIMEOUT_MILI ; 
 scalar_t__ fw_initializing (struct mlx5_core_dev*) ; 
 unsigned long jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int) ; 
 unsigned long msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_fw_init(struct mlx5_core_dev *dev, u32 max_wait_mili,
			u32 warn_time_mili)
{
	unsigned long warn = jiffies + msecs_to_jiffies(warn_time_mili);
	unsigned long end = jiffies + msecs_to_jiffies(max_wait_mili);
	int err = 0;

	BUILD_BUG_ON(FW_PRE_INIT_TIMEOUT_MILI < FW_INIT_WARN_MESSAGE_INTERVAL);

	while (fw_initializing(dev)) {
		if (time_after(jiffies, end)) {
			err = -EBUSY;
			break;
		}
		if (warn_time_mili && time_after(jiffies, warn)) {
			mlx5_core_warn(dev, "Waiting for FW initialization, timeout abort in %ds\n",
				       jiffies_to_msecs(end - warn) / 1000);
			warn = jiffies + msecs_to_jiffies(warn_time_mili);
		}
		msleep(FW_INIT_WAIT_MS);
	}

	return err;
}