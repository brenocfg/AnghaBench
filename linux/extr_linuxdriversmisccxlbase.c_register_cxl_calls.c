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
struct cxl_calls {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ cxl_calls ; 
 int /*<<< orphan*/  rcu_assign_pointer (scalar_t__,struct cxl_calls*) ; 

int register_cxl_calls(struct cxl_calls *calls)
{
	if (cxl_calls)
		return -EBUSY;

	rcu_assign_pointer(cxl_calls, calls);
	return 0;
}