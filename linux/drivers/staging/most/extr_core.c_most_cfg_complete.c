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
struct core_component {int (* cfg_complete ) () ;} ;

/* Variables and functions */
 int ENODEV ; 
 struct core_component* match_component (char*) ; 
 int stub1 () ; 

int most_cfg_complete(char *comp_name)
{
	struct core_component *comp;

	comp = match_component(comp_name);
	if (!comp)
		return -ENODEV;

	return comp->cfg_complete();
}