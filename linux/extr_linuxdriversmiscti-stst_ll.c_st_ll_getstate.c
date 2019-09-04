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
struct st_data_s {unsigned long ll_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 

unsigned long st_ll_getstate(struct st_data_s *ll)
{
	pr_debug(" returning state %ld", ll->ll_state);
	return ll->ll_state;
}