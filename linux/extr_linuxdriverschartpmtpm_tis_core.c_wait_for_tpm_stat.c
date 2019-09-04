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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  int u8 ;
struct tpm_chip {int flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* status ) (struct tpm_chip*) ;} ;

/* Variables and functions */
 int ECANCELED ; 
 long ERESTARTSYS ; 
 int ETIME ; 
 int /*<<< orphan*/  TIF_SIGPENDING ; 
 int TPM_CHIP_FLAG_IRQ ; 
 int /*<<< orphan*/  TPM_TIMEOUT_USECS_MAX ; 
 int /*<<< orphan*/  TPM_TIMEOUT_USECS_MIN ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ freezing (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int stub1 (struct tpm_chip*) ; 
 int stub2 (struct tpm_chip*) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wait_for_tpm_stat_cond (struct tpm_chip*,int,int,int*) ; 

__attribute__((used)) static int wait_for_tpm_stat(struct tpm_chip *chip, u8 mask,
		unsigned long timeout, wait_queue_head_t *queue,
		bool check_cancel)
{
	unsigned long stop;
	long rc;
	u8 status;
	bool canceled = false;

	/* check current status */
	status = chip->ops->status(chip);
	if ((status & mask) == mask)
		return 0;

	stop = jiffies + timeout;

	if (chip->flags & TPM_CHIP_FLAG_IRQ) {
again:
		timeout = stop - jiffies;
		if ((long)timeout <= 0)
			return -ETIME;
		rc = wait_event_interruptible_timeout(*queue,
			wait_for_tpm_stat_cond(chip, mask, check_cancel,
					       &canceled),
			timeout);
		if (rc > 0) {
			if (canceled)
				return -ECANCELED;
			return 0;
		}
		if (rc == -ERESTARTSYS && freezing(current)) {
			clear_thread_flag(TIF_SIGPENDING);
			goto again;
		}
	} else {
		do {
			usleep_range(TPM_TIMEOUT_USECS_MIN,
				     TPM_TIMEOUT_USECS_MAX);
			status = chip->ops->status(chip);
			if ((status & mask) == mask)
				return 0;
		} while (time_before(jiffies, stop));
	}
	return -ETIME;
}