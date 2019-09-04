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
struct iop_adma_chan {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __iop_adma_slot_cleanup (struct iop_adma_chan*) ; 
 int /*<<< orphan*/  spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iop_adma_tasklet(unsigned long data)
{
	struct iop_adma_chan *iop_chan = (struct iop_adma_chan *) data;

	/* lockdep will flag depedency submissions as potentially
	 * recursive locking, this is not the case as a dependency
	 * submission will never recurse a channels submit routine.
	 * There are checks in async_tx.c to prevent this.
	 */
	spin_lock_nested(&iop_chan->lock, SINGLE_DEPTH_NESTING);
	__iop_adma_slot_cleanup(iop_chan);
	spin_unlock(&iop_chan->lock);
}