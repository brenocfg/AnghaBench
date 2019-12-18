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
struct reset_control {int acquired; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct reset_control*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_array_release (int /*<<< orphan*/ ) ; 
 scalar_t__ reset_control_is_array (struct reset_control*) ; 
 int /*<<< orphan*/  rstc_to_array (struct reset_control*) ; 

void reset_control_release(struct reset_control *rstc)
{
	if (!rstc || WARN_ON(IS_ERR(rstc)))
		return;

	if (reset_control_is_array(rstc))
		reset_control_array_release(rstc_to_array(rstc));
	else
		rstc->acquired = false;
}