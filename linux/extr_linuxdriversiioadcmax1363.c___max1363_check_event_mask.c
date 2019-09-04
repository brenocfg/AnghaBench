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
 int EBUSY ; 

__attribute__((used)) static inline int __max1363_check_event_mask(int thismask, int checkmask)
{
	int ret = 0;
	/* Is it unipolar */
	if (thismask < 4) {
		if (checkmask & ~0x0F) {
			ret = -EBUSY;
			goto error_ret;
		}
	} else if (thismask < 6) {
		if (checkmask & ~0x30) {
			ret = -EBUSY;
			goto error_ret;
		}
	} else if (checkmask & ~0xC0)
		ret = -EBUSY;
error_ret:
	return ret;
}