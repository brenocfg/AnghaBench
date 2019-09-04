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

/* Variables and functions */
 int MAX_8042_FF ; 
 int MAX_8042_LOOPS ; 
 int inb (int) ; 
 int /*<<< orphan*/  io_delay () ; 

__attribute__((used)) static int empty_8042(void)
{
	u8 status;
	int loops = MAX_8042_LOOPS;
	int ffs   = MAX_8042_FF;

	while (loops--) {
		io_delay();

		status = inb(0x64);
		if (status == 0xff) {
			/* FF is a plausible, but very unlikely status */
			if (!--ffs)
				return -1; /* Assume no KBC present */
		}
		if (status & 1) {
			/* Read and discard input data */
			io_delay();
			(void)inb(0x60);
		} else if (!(status & 2)) {
			/* Buffers empty, finished! */
			return 0;
		}
	}

	return -1;
}