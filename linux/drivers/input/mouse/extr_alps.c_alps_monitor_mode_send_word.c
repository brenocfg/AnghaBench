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
 scalar_t__ alps_command_mode_send_nibble (struct psmouse*,int) ; 

__attribute__((used)) static int alps_monitor_mode_send_word(struct psmouse *psmouse, u16 word)
{
	int i, nibble;

	/*
	 * b0-b11 are valid bits, send sequence is inverse.
	 * e.g. when word = 0x0123, nibble send sequence is 3, 2, 1
	 */
	for (i = 0; i <= 8; i += 4) {
		nibble = (word >> i) & 0xf;
		if (alps_command_mode_send_nibble(psmouse, nibble))
			return -1;
	}

	return 0;
}