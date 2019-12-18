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
struct i3c_master_controller_ops {int /*<<< orphan*/  recycle_ibi_slot; int /*<<< orphan*/  free_ibi; int /*<<< orphan*/  disable_ibi; int /*<<< orphan*/  enable_ibi; scalar_t__ request_ibi; int /*<<< orphan*/  i2c_xfers; int /*<<< orphan*/  do_daa; int /*<<< orphan*/  send_ccc_cmd; int /*<<< orphan*/  priv_xfers; int /*<<< orphan*/  bus_init; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int i3c_master_check_ops(const struct i3c_master_controller_ops *ops)
{
	if (!ops || !ops->bus_init || !ops->priv_xfers ||
	    !ops->send_ccc_cmd || !ops->do_daa || !ops->i2c_xfers)
		return -EINVAL;

	if (ops->request_ibi &&
	    (!ops->enable_ibi || !ops->disable_ibi || !ops->free_ibi ||
	     !ops->recycle_ibi_slot))
		return -EINVAL;

	return 0;
}