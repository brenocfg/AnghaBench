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
struct mcu {int reg_ctrl; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int MCU_CTRL_BTN ; 
 int /*<<< orphan*/  MCU_REG_CTRL ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  ctrl_alt_del () ; 
 struct mcu* glob_mcu ; 
 int i2c_smbus_read_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int shutdown_thread_fn(void *data)
{
	int ret;
	struct mcu *mcu = glob_mcu;

	while (!kthread_should_stop()) {
		ret = i2c_smbus_read_byte_data(mcu->client, MCU_REG_CTRL);
		if (ret < 0)
			pr_err("MCU status reg read failed.\n");
		mcu->reg_ctrl = ret;


		if (mcu->reg_ctrl & MCU_CTRL_BTN) {
			i2c_smbus_write_byte_data(mcu->client, MCU_REG_CTRL,
						  mcu->reg_ctrl & ~MCU_CTRL_BTN);

			ctrl_alt_del();
		}

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_timeout(HZ);
	}

	return 0;
}