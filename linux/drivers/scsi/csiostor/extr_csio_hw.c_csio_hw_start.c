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
struct csio_hw {int /*<<< orphan*/  lock; int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_HWE_CFG ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  csio_hws_uninit ; 
 scalar_t__ csio_is_hw_ready (struct csio_hw*) ; 
 scalar_t__ csio_match_state (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_post_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
csio_hw_start(struct csio_hw *hw)
{
	spin_lock_irq(&hw->lock);
	csio_post_event(&hw->sm, CSIO_HWE_CFG);
	spin_unlock_irq(&hw->lock);

	if (csio_is_hw_ready(hw))
		return 0;
	else if (csio_match_state(hw, csio_hws_uninit))
		return -EINVAL;
	else
		return -ENODEV;
}