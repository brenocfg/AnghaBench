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
struct hfa384x {int /*<<< orphan*/  commsqual_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  commsqual_timer ; 
 struct hfa384x* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct hfa384x* hw ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void prism2sta_commsqual_timer(struct timer_list *t)
{
	struct hfa384x *hw = from_timer(hw, t, commsqual_timer);

	schedule_work(&hw->commsqual_bh);
}