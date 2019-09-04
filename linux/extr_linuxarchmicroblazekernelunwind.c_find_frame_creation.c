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
typedef  int s16 ;

/* Variables and functions */
 int get_frame_size (unsigned long) ; 
 int /*<<< orphan*/  kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static unsigned long *find_frame_creation(unsigned long *pc)
{
	int i;

	/* NOTE: Distance to search is arbitrary
	 *	 250 works well for most things,
	 *	 750 picks up things like tcp_recvmsg(),
	 *	1000 needed for fat_fill_super()
	 */
	for (i = 0; i < 1000; i++, pc--) {
		unsigned long instr;
		s16 frame_size;

		if (!kernel_text_address((unsigned long) pc))
			return NULL;

		instr = *pc;

		/* addik r1, r1, foo ? */
		if ((instr & 0xFFFF0000) != 0x30210000)
			continue;	/* No */

		frame_size = get_frame_size(instr);
		if ((frame_size < 8) || (frame_size & 3)) {
			pr_debug("    Invalid frame size %d at 0x%p\n",
				 frame_size, pc);
			return NULL;
		}

		pr_debug("    Found frame creation at 0x%p, size %d\n", pc,
			 frame_size);
		return pc;
	}

	return NULL;
}