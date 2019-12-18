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
struct timer_list {int dummy; } ;
struct recv_reorder_ctrl {int dummy; } ;

/* Variables and functions */
 struct recv_reorder_ctrl* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_reordering_ctrl_timeout_handler (struct recv_reorder_ctrl*) ; 
 struct recv_reorder_ctrl* reorder_ctrl ; 
 int /*<<< orphan*/  reordering_ctrl_timer ; 

__attribute__((used)) static void _r8712_reordering_ctrl_timeout_handler (struct timer_list *t)
{
	struct recv_reorder_ctrl *reorder_ctrl =
			 from_timer(reorder_ctrl, t, reordering_ctrl_timer);

	r8712_reordering_ctrl_timeout_handler(reorder_ctrl);
}