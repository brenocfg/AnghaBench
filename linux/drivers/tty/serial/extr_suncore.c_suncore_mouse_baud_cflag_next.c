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
struct TYPE_2__ {int baud; unsigned int cflag; } ;

/* Variables and functions */
 unsigned int CBAUD ; 
 TYPE_1__* mouse_baud_table ; 

unsigned int suncore_mouse_baud_cflag_next(unsigned int cflag, int *new_baud)
{
	int i;

	for (i = 0; mouse_baud_table[i].baud != -1; i++)
		if (mouse_baud_table[i].cflag == (cflag & CBAUD))
			break;

	i += 1;
	if (mouse_baud_table[i].baud == -1)
		i = 0;

	*new_baud = mouse_baud_table[i].baud;
	return mouse_baud_table[i].cflag;
}