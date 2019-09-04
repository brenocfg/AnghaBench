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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_paste_address (struct vas_window*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

u64 vas_win_paste_addr(struct vas_window *win)
{
	u64 addr;

	compute_paste_address(win, &addr, NULL);

	return addr;
}