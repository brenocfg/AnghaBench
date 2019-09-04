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
struct mvebu_mbus_state {TYPE_1__* soc; } ;
struct TYPE_2__ {scalar_t__ (* win_remap_offset ) (int const) ;} ;

/* Variables and functions */
 scalar_t__ MVEBU_MBUS_NO_REMAP ; 
 scalar_t__ stub1 (int const) ; 

__attribute__((used)) static bool mvebu_mbus_window_is_remappable(struct mvebu_mbus_state *mbus,
					    const int win)
{
	return mbus->soc->win_remap_offset(win) != MVEBU_MBUS_NO_REMAP;
}