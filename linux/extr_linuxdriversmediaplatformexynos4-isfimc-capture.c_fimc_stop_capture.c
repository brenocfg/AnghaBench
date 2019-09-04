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
struct fimc_dev {int /*<<< orphan*/  state; int /*<<< orphan*/  irq_queue; int /*<<< orphan*/  slock; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  ST_CAPT_SHUT ; 
 int /*<<< orphan*/  fimc_capture_active (struct fimc_dev*) ; 
 int fimc_capture_state_cleanup (struct fimc_dev*,int) ; 
 int /*<<< orphan*/  fimc_deactivate_capture (struct fimc_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int fimc_stop_capture(struct fimc_dev *fimc, bool suspend)
{
	unsigned long flags;

	if (!fimc_capture_active(fimc))
		return 0;

	spin_lock_irqsave(&fimc->slock, flags);
	set_bit(ST_CAPT_SHUT, &fimc->state);
	fimc_deactivate_capture(fimc);
	spin_unlock_irqrestore(&fimc->slock, flags);

	wait_event_timeout(fimc->irq_queue,
			   !test_bit(ST_CAPT_SHUT, &fimc->state),
			   (2*HZ/10)); /* 200 ms */

	return fimc_capture_state_cleanup(fimc, suspend);
}