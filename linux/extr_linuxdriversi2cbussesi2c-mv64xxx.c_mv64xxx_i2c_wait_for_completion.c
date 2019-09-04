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
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout; } ;
struct mv64xxx_i2c_data {long rc; int aborting; int /*<<< orphan*/  lock; scalar_t__ block; TYPE_1__ adapter; int /*<<< orphan*/  state; int /*<<< orphan*/  waitq; } ;

/* Variables and functions */
 long ETIMEDOUT ; 
 int /*<<< orphan*/  MV64XXX_I2C_STATE_IDLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  mv64xxx_i2c_hw_init (struct mv64xxx_i2c_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv64xxx_i2c_wait_for_completion(struct mv64xxx_i2c_data *drv_data)
{
	long		time_left;
	unsigned long	flags;
	char		abort = 0;

	time_left = wait_event_timeout(drv_data->waitq,
		!drv_data->block, drv_data->adapter.timeout);

	spin_lock_irqsave(&drv_data->lock, flags);
	if (!time_left) { /* Timed out */
		drv_data->rc = -ETIMEDOUT;
		abort = 1;
	} else if (time_left < 0) { /* Interrupted/Error */
		drv_data->rc = time_left; /* errno value */
		abort = 1;
	}

	if (abort && drv_data->block) {
		drv_data->aborting = 1;
		spin_unlock_irqrestore(&drv_data->lock, flags);

		time_left = wait_event_timeout(drv_data->waitq,
			!drv_data->block, drv_data->adapter.timeout);

		if ((time_left <= 0) && drv_data->block) {
			drv_data->state = MV64XXX_I2C_STATE_IDLE;
			dev_err(&drv_data->adapter.dev,
				"mv64xxx: I2C bus locked, block: %d, "
				"time_left: %d\n", drv_data->block,
				(int)time_left);
			mv64xxx_i2c_hw_init(drv_data);
		}
	} else
		spin_unlock_irqrestore(&drv_data->lock, flags);
}