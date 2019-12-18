#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_lsm6dsx_hw {int /*<<< orphan*/  fifo_lock; TYPE_2__* settings; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_fifo ) (struct st_lsm6dsx_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ fifo_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_LSM6DSX_FIFO_BYPASS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int st_lsm6dsx_set_fifo_mode (struct st_lsm6dsx_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct st_lsm6dsx_hw*) ; 

int st_lsm6dsx_flush_fifo(struct st_lsm6dsx_hw *hw)
{
	int err;

	mutex_lock(&hw->fifo_lock);

	hw->settings->fifo_ops.read_fifo(hw);
	err = st_lsm6dsx_set_fifo_mode(hw, ST_LSM6DSX_FIFO_BYPASS);

	mutex_unlock(&hw->fifo_lock);

	return err;
}