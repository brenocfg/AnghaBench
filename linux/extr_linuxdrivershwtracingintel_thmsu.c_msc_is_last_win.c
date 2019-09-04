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
struct TYPE_3__ {int /*<<< orphan*/ * next; } ;
struct msc_window {TYPE_2__* msc; TYPE_1__ entry; } ;
struct TYPE_4__ {int /*<<< orphan*/  win_list; } ;

/* Variables and functions */

__attribute__((used)) static inline bool msc_is_last_win(struct msc_window *win)
{
	return win->entry.next == &win->msc->win_list;
}