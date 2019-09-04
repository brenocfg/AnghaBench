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
typedef  int u8 ;
struct psmouse {int dummy; } ;

/* Variables and functions */
 scalar_t__ alps_command_mode_send_nibble (struct psmouse*,int) ; 

__attribute__((used)) static int __alps_command_mode_write_reg(struct psmouse *psmouse, u8 value)
{
	if (alps_command_mode_send_nibble(psmouse, (value >> 4) & 0xf))
		return -1;
	if (alps_command_mode_send_nibble(psmouse, value & 0xf))
		return -1;
	return 0;
}