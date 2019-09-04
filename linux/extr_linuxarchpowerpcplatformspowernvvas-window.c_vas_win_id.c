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
typedef  int /*<<< orphan*/  u32 ;
struct vas_window {int /*<<< orphan*/  winid; TYPE_1__* vinst; } ;
struct TYPE_2__ {int /*<<< orphan*/  vas_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  encode_pswid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u32 vas_win_id(struct vas_window *win)
{
	return encode_pswid(win->vinst->vas_id, win->winid);
}