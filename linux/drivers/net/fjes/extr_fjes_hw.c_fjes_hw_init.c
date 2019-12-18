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
struct TYPE_2__ {int /*<<< orphan*/  trace_size; int /*<<< orphan*/  trace; int /*<<< orphan*/  lock; } ;
struct fjes_hw {scalar_t__ max_epid; scalar_t__ my_epid; TYPE_1__ hw_info; int /*<<< orphan*/  rx_status_lock; int /*<<< orphan*/  epstop_task; int /*<<< orphan*/  update_zone_task; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  FJES_DEBUG_BUFFER_SIZE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ICTL_MASK_ALL ; 
 int /*<<< orphan*/  fjes_hw_epstop_task ; 
 scalar_t__ fjes_hw_get_max_epid (struct fjes_hw*) ; 
 scalar_t__ fjes_hw_get_my_epid (struct fjes_hw*) ; 
 int /*<<< orphan*/  fjes_hw_iomap (struct fjes_hw*) ; 
 int fjes_hw_reset (struct fjes_hw*) ; 
 int /*<<< orphan*/  fjes_hw_set_irqmask (struct fjes_hw*,int /*<<< orphan*/ ,int) ; 
 int fjes_hw_setup (struct fjes_hw*) ; 
 int /*<<< orphan*/  fjes_hw_update_zone_task ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vzalloc (int /*<<< orphan*/ ) ; 

int fjes_hw_init(struct fjes_hw *hw)
{
	int ret;

	hw->base = fjes_hw_iomap(hw);
	if (!hw->base)
		return -EIO;

	ret = fjes_hw_reset(hw);
	if (ret)
		return ret;

	fjes_hw_set_irqmask(hw, REG_ICTL_MASK_ALL, true);

	INIT_WORK(&hw->update_zone_task, fjes_hw_update_zone_task);
	INIT_WORK(&hw->epstop_task, fjes_hw_epstop_task);

	mutex_init(&hw->hw_info.lock);
	spin_lock_init(&hw->rx_status_lock);

	hw->max_epid = fjes_hw_get_max_epid(hw);
	hw->my_epid = fjes_hw_get_my_epid(hw);

	if ((hw->max_epid == 0) || (hw->my_epid >= hw->max_epid))
		return -ENXIO;

	ret = fjes_hw_setup(hw);

	hw->hw_info.trace = vzalloc(FJES_DEBUG_BUFFER_SIZE);
	hw->hw_info.trace_size = FJES_DEBUG_BUFFER_SIZE;

	return ret;
}