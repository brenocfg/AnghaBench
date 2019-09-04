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

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_string ; 
 scalar_t__ jiffies ; 
 scalar_t__ max_display_count ; 
 int /*<<< orphan*/  mips_scroll_timer ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void mips_scroll_message(void)
{
	del_timer_sync(&mips_scroll_timer);
	max_display_count = strlen(display_string) + 1 - 8;
	mod_timer(&mips_scroll_timer, jiffies + 1);
}