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
struct csio_hw {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbfn_q ; 
 int /*<<< orphan*/  csio_mb_cancel_all (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_mb_completions (struct csio_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_hw_mbm_cleanup(struct csio_hw *hw)
{
	LIST_HEAD(cbfn_q);

	csio_mb_cancel_all(hw, &cbfn_q);

	spin_unlock_irq(&hw->lock);
	csio_mb_completions(hw, &cbfn_q);
	spin_lock_irq(&hw->lock);
}