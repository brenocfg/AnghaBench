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
struct TYPE_2__ {int (* get_exception ) () ;} ;

/* Variables and functions */
 TYPE_1__ soc_ops ; 
 int stub1 () ; 

int soc_get_exception(void)
{
	if (!soc_ops.get_exception)
		return -1;
	return soc_ops.get_exception();
}