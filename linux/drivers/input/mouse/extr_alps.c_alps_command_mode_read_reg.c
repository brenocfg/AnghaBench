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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int __alps_command_mode_read_reg (struct psmouse*,int) ; 
 scalar_t__ alps_command_mode_set_addr (struct psmouse*,int) ; 

__attribute__((used)) static int alps_command_mode_read_reg(struct psmouse *psmouse, int addr)
{
	if (alps_command_mode_set_addr(psmouse, addr))
		return -1;
	return __alps_command_mode_read_reg(psmouse, addr);
}