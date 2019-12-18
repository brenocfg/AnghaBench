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
struct fsg_common {int /*<<< orphan*/  io_wait; } ;
struct fsg_buffhd {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ BUF_STATE_EMPTY ; 
 int EINTR ; 
 scalar_t__ smp_load_acquire (int /*<<< orphan*/ *) ; 
 int wait_event_freezable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sleep_thread(struct fsg_common *common, bool can_freeze,
		struct fsg_buffhd *bh)
{
	int	rc;

	/* Wait until a signal arrives or bh is no longer busy */
	if (can_freeze)
		/*
		 * synchronize with the smp_store_release(&bh->state) in
		 * bulk_in_complete() or bulk_out_complete()
		 */
		rc = wait_event_freezable(common->io_wait,
				bh && smp_load_acquire(&bh->state) >=
					BUF_STATE_EMPTY);
	else
		rc = wait_event_interruptible(common->io_wait,
				bh && smp_load_acquire(&bh->state) >=
					BUF_STATE_EMPTY);
	return rc ? -EINTR : 0;
}