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
struct loop_device {scalar_t__ lo_state; int use_dio; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ Lo_bound ; 
 int /*<<< orphan*/  __loop_update_dio (struct loop_device*,int) ; 

__attribute__((used)) static int loop_set_dio(struct loop_device *lo, unsigned long arg)
{
	int error = -ENXIO;
	if (lo->lo_state != Lo_bound)
		goto out;

	__loop_update_dio(lo, !!arg);
	if (lo->use_dio == !!arg)
		return 0;
	error = -EINVAL;
 out:
	return error;
}