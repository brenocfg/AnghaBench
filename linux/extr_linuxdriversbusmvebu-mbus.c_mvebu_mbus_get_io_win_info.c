#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_5__ {TYPE_1__* soc; } ;
struct TYPE_4__ {int num_wins; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ mbus_state ; 
 int /*<<< orphan*/  mvebu_mbus_read_window (TYPE_2__*,int,int*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int mvebu_mbus_get_io_win_info(phys_addr_t phyaddr, u32 *size, u8 *target,
			       u8 *attr)
{
	int win;

	for (win = 0; win < mbus_state.soc->num_wins; win++) {
		u64 wbase;
		int enabled;

		mvebu_mbus_read_window(&mbus_state, win, &enabled, &wbase,
				       size, target, attr, NULL);

		if (!enabled)
			continue;

		if (wbase <= phyaddr && phyaddr <= wbase + *size)
			return win;
	}

	return -EINVAL;
}