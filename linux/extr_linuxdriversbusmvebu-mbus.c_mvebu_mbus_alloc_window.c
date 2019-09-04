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
typedef  int /*<<< orphan*/  u8 ;
struct mvebu_mbus_state {TYPE_1__* soc; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int num_wins; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MVEBU_MBUS_NO_REMAP ; 
 int mvebu_mbus_setup_window (struct mvebu_mbus_state*,int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mvebu_mbus_window_is_free (struct mvebu_mbus_state*,int) ; 
 scalar_t__ mvebu_mbus_window_is_remappable (struct mvebu_mbus_state*,int) ; 

__attribute__((used)) static int mvebu_mbus_alloc_window(struct mvebu_mbus_state *mbus,
				   phys_addr_t base, size_t size,
				   phys_addr_t remap, u8 target,
				   u8 attr)
{
	int win;

	if (remap == MVEBU_MBUS_NO_REMAP) {
		for (win = 0; win < mbus->soc->num_wins; win++) {
			if (mvebu_mbus_window_is_remappable(mbus, win))
				continue;

			if (mvebu_mbus_window_is_free(mbus, win))
				return mvebu_mbus_setup_window(mbus, win, base,
							       size, remap,
							       target, attr);
		}
	}

	for (win = 0; win < mbus->soc->num_wins; win++) {
		/* Skip window if need remap but is not supported */
		if ((remap != MVEBU_MBUS_NO_REMAP) &&
		    !mvebu_mbus_window_is_remappable(mbus, win))
			continue;

		if (mvebu_mbus_window_is_free(mbus, win))
			return mvebu_mbus_setup_window(mbus, win, base, size,
						       remap, target, attr);
	}

	return -ENOMEM;
}