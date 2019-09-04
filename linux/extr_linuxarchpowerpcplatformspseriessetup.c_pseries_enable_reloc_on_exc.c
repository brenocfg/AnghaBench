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
 int /*<<< orphan*/  H_IS_LONG_BUSY (long) ; 
 long H_P2 ; 
 long H_SUCCESS ; 
 long enable_reloc_on_exceptions () ; 
 unsigned int get_longbusy_msecs (long) ; 
 int /*<<< orphan*/  mdelay (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,unsigned int) ; 

void pseries_enable_reloc_on_exc(void)
{
	long rc;
	unsigned int delay, total_delay = 0;

	while (1) {
		rc = enable_reloc_on_exceptions();
		if (!H_IS_LONG_BUSY(rc)) {
			if (rc == H_P2) {
				pr_info("Relocation on exceptions not"
					" supported\n");
			} else if (rc != H_SUCCESS) {
				pr_warn("Unable to enable relocation"
					" on exceptions: %ld\n", rc);
			}
			break;
		}

		delay = get_longbusy_msecs(rc);
		total_delay += delay;
		if (total_delay > 1000) {
			pr_warn("Warning: Giving up waiting to enable "
				"relocation on exceptions (%u msec)!\n",
				total_delay);
			return;
		}

		mdelay(delay);
	}
}