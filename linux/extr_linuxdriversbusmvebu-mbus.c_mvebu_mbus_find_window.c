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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct mvebu_mbus_state {TYPE_1__* soc; } ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {int num_wins; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  mvebu_mbus_read_window (struct mvebu_mbus_state*,int,int*,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mvebu_mbus_find_window(struct mvebu_mbus_state *mbus,
				  phys_addr_t base, size_t size)
{
	int win;

	for (win = 0; win < mbus->soc->num_wins; win++) {
		u64 wbase;
		u32 wsize;
		int enabled;

		mvebu_mbus_read_window(mbus, win,
				       &enabled, &wbase, &wsize,
				       NULL, NULL, NULL);

		if (!enabled)
			continue;

		if (base == wbase && size == wsize)
			return win;
	}

	return -ENODEV;
}