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
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_CONSOLE_UNLOCKED () ; 
 scalar_t__ con_should_update (struct vc_data*) ; 
 int /*<<< orphan*/  do_update_region (struct vc_data*,unsigned long,int) ; 
 int /*<<< orphan*/  hide_cursor (struct vc_data*) ; 
 int /*<<< orphan*/  set_cursor (struct vc_data*) ; 

void update_region(struct vc_data *vc, unsigned long start, int count)
{
	WARN_CONSOLE_UNLOCKED();

	if (con_should_update(vc)) {
		hide_cursor(vc);
		do_update_region(vc, start, count);
		set_cursor(vc);
	}
}