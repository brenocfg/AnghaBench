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
 int /*<<< orphan*/  CMOS_READ (unsigned int) ; 
 scalar_t__ NVRAM_OFFSET ; 
 scalar_t__ can_bank2 ; 
 int /*<<< orphan*/  cmos_read_bank2 (unsigned int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmos_nvram_read(void *priv, unsigned int off, void *val,
			   size_t count)
{
	unsigned char *buf = val;
	int	retval;

	off += NVRAM_OFFSET;
	spin_lock_irq(&rtc_lock);
	for (retval = 0; count; count--, off++, retval++) {
		if (off < 128)
			*buf++ = CMOS_READ(off);
		else if (can_bank2)
			*buf++ = cmos_read_bank2(off);
		else
			break;
	}
	spin_unlock_irq(&rtc_lock);

	return retval;
}