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
 int /*<<< orphan*/  DE_STATE2 ; 
 unsigned int DE_STATE2_DE_FIFO_EMPTY ; 
 unsigned int DE_STATE2_DE_MEM_FIFO_EMPTY ; 
 unsigned int DE_STATE2_DE_STATUS_BUSY ; 
 unsigned int peek32 (int /*<<< orphan*/ ) ; 

int hw_sm750le_deWait(void)
{
	int i = 0x10000000;
	unsigned int mask = DE_STATE2_DE_STATUS_BUSY | DE_STATE2_DE_FIFO_EMPTY |
		DE_STATE2_DE_MEM_FIFO_EMPTY;

	while (i--) {
		unsigned int val = peek32(DE_STATE2);

		if ((val & mask) ==
		    (DE_STATE2_DE_FIFO_EMPTY | DE_STATE2_DE_MEM_FIFO_EMPTY))
			return 0;
	}
	/* timeout error */
	return -1;
}