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
typedef  size_t u16 ;
struct hfa384x {scalar_t__* port_enabled; scalar_t__ isap; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t HFA384x_PORTID_MAX ; 
 int hfa384x_cmd_disable (struct hfa384x*,size_t) ; 

int hfa384x_drvr_disable(struct hfa384x *hw, u16 macport)
{
	int result = 0;

	if ((!hw->isap && macport != 0) ||
	    (hw->isap && !(macport <= HFA384x_PORTID_MAX)) ||
	    !(hw->port_enabled[macport])) {
		result = -EINVAL;
	} else {
		result = hfa384x_cmd_disable(hw, macport);
		if (result == 0)
			hw->port_enabled[macport] = 0;
	}
	return result;
}