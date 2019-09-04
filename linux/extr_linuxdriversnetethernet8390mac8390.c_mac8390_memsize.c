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
 scalar_t__ hwreg_present (unsigned short volatile*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static int mac8390_memsize(unsigned long membase)
{
	unsigned long flags;
	int i, j;

	local_irq_save(flags);
	/* Check up to 32K in 4K increments */
	for (i = 0; i < 8; i++) {
		volatile unsigned short *m = (unsigned short *)(membase + (i * 0x1000));

		/* Unwriteable - we have a fully decoded card and the
		   RAM end located */
		if (hwreg_present(m) == 0)
			break;

		/* write a distinctive byte */
		*m = 0xA5A0 | i;
		/* check that we read back what we wrote */
		if (*m != (0xA5A0 | i))
			break;

		/* check for partial decode and wrap */
		for (j = 0; j < i; j++) {
			volatile unsigned short *p = (unsigned short *)(membase + (j * 0x1000));
			if (*p != (0xA5A0 | j))
				break;
		}
	}
	local_irq_restore(flags);
	/*
	 * in any case, we stopped once we tried one block too many,
	 * or once we reached 32K
	 */
	return i * 0x1000;
}