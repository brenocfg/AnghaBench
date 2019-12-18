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

/* Variables and functions */
 unsigned char EXTENDED_MESSAGE ; 
 unsigned char EXTENDED_SDTR ; 

int spi_populate_sync_msg(unsigned char *msg, int period, int offset)
{
	msg[0] = EXTENDED_MESSAGE;
	msg[1] = 3;
	msg[2] = EXTENDED_SDTR;
	msg[3] = period;
	msg[4] = offset;
	return 5;
}