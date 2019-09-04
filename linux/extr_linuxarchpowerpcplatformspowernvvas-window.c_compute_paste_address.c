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
typedef  int u64 ;
struct vas_window {int winid; TYPE_1__* vinst; } ;
struct TYPE_2__ {int paste_base_addr; int paste_win_id_shift; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static void compute_paste_address(struct vas_window *window, u64 *addr, int *len)
{
	int winid;
	u64 base, shift;

	base = window->vinst->paste_base_addr;
	shift = window->vinst->paste_win_id_shift;
	winid = window->winid;

	*addr  = base + (winid << shift);
	if (len)
		*len = PAGE_SIZE;

	pr_debug("Txwin #%d: Paste addr 0x%llx\n", winid, *addr);
}