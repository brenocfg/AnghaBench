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
struct iwl_txq {scalar_t__ read_ptr; scalar_t__ write_ptr; scalar_t__ wd_timeout; int /*<<< orphan*/  stuck_timer; scalar_t__ frozen; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void iwl_pcie_txq_progress(struct iwl_txq *txq)
{
	lockdep_assert_held(&txq->lock);

	if (!txq->wd_timeout)
		return;

	/*
	 * station is asleep and we send data - that must
	 * be uAPSD or PS-Poll. Don't rearm the timer.
	 */
	if (txq->frozen)
		return;

	/*
	 * if empty delete timer, otherwise move timer forward
	 * since we're making progress on this queue
	 */
	if (txq->read_ptr == txq->write_ptr)
		del_timer(&txq->stuck_timer);
	else
		mod_timer(&txq->stuck_timer, jiffies + txq->wd_timeout);
}