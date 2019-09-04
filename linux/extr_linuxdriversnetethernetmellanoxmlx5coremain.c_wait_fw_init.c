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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FW_INIT_WAIT_MS ; 
 scalar_t__ fw_initializing (struct mlx5_core_dev*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int wait_fw_init(struct mlx5_core_dev *dev, u32 max_wait_mili)
{
	unsigned long end = jiffies + msecs_to_jiffies(max_wait_mili);
	int err = 0;

	while (fw_initializing(dev)) {
		if (time_after(jiffies, end)) {
			err = -EBUSY;
			break;
		}
		msleep(FW_INIT_WAIT_MS);
	}

	return err;
}