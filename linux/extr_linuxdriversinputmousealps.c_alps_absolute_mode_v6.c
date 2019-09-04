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
typedef  int u16 ;
struct psmouse {int dummy; } ;

/* Variables and functions */
 scalar_t__ alps_monitor_mode (struct psmouse*,int) ; 
 int alps_monitor_mode_write_reg (struct psmouse*,int,int) ; 

__attribute__((used)) static int alps_absolute_mode_v6(struct psmouse *psmouse)
{
	u16 reg_val = 0x181;
	int ret = -1;

	/* enter monitor mode, to write the register */
	if (alps_monitor_mode(psmouse, true))
		return -1;

	ret = alps_monitor_mode_write_reg(psmouse, 0x000, reg_val);

	if (alps_monitor_mode(psmouse, false))
		ret = -1;

	return ret;
}