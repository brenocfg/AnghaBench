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

__attribute__((used)) static void dump_status_reg(unsigned long *status)
{
#ifdef DEBUG
	pr_debug("machxo2 status: 0x%08lX - done=%d, cfgena=%d, busy=%d, fail=%d, devver=%d, err=%s\n",
		 *status, test_bit(DONE, status), test_bit(ENAB, status),
		 test_bit(BUSY, status), test_bit(FAIL, status),
		 test_bit(DVER, status), get_err_string(get_err(status)));
#endif
}