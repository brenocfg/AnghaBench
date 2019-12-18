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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct m5mols_info {int /*<<< orphan*/  irq_done; int /*<<< orphan*/  irq_waitq; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int M5MOLS_I2C_RDY_WAIT_FL ; 
 int /*<<< orphan*/  SYSTEM_INT_FACTOR ; 
 int /*<<< orphan*/  atomic_add_unless (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int m5mols_busy_wait (struct v4l2_subdev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 struct m5mols_info* to_m5mols (struct v4l2_subdev*) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int m5mols_wait_interrupt(struct v4l2_subdev *sd, u8 irq_mask, u32 timeout)
{
	struct m5mols_info *info = to_m5mols(sd);

	int ret = wait_event_interruptible_timeout(info->irq_waitq,
				atomic_add_unless(&info->irq_done, -1, 0),
				msecs_to_jiffies(timeout));
	if (ret <= 0)
		return ret ? ret : -ETIMEDOUT;

	return m5mols_busy_wait(sd, SYSTEM_INT_FACTOR, irq_mask,
				M5MOLS_I2C_RDY_WAIT_FL | irq_mask, -1);
}