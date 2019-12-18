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
typedef  int u32 ;
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_PENDING ; 
 int /*<<< orphan*/  AF_DISC_PENDING ; 
 int DRBL_FLASH_DONE ; 
 int DRBL_FLASH_REQ ; 
 int /*<<< orphan*/  MU_DOORBELL_IN ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int MU_INTSTAT_DRBL ; 
 int /*<<< orphan*/  MU_INT_STATUS_OUT ; 
 int /*<<< orphan*/  esas2r_disable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_enable_chip_interrupts (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool esas2r_flash_access(struct esas2r_adapter *a, u32 function)
{
	u32 starttime;
	u32 timeout;
	u32 intstat;
	u32 doorbell;

	/* Disable chip interrupts awhile */
	if (function == DRBL_FLASH_REQ)
		esas2r_disable_chip_interrupts(a);

	/* Issue the request to the firmware */
	esas2r_write_register_dword(a, MU_DOORBELL_IN, function);

	/* Now wait for the firmware to process it */
	starttime = jiffies_to_msecs(jiffies);

	if (test_bit(AF_CHPRST_PENDING, &a->flags) ||
	    test_bit(AF_DISC_PENDING, &a->flags))
		timeout = 40000;
	else
		timeout = 5000;

	while (true) {
		intstat = esas2r_read_register_dword(a, MU_INT_STATUS_OUT);

		if (intstat & MU_INTSTAT_DRBL) {
			/* Got a doorbell interrupt.  Check for the function */
			doorbell =
				esas2r_read_register_dword(a, MU_DOORBELL_OUT);
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);
			if (doorbell & function)
				break;
		}

		schedule_timeout_interruptible(msecs_to_jiffies(100));

		if ((jiffies_to_msecs(jiffies) - starttime) > timeout) {
			/*
			 * Iimeout.  If we were requesting flash access,
			 * indicate we are done so the firmware knows we gave
			 * up.  If this was a REQ, we also need to re-enable
			 * chip interrupts.
			 */
			if (function == DRBL_FLASH_REQ) {
				esas2r_hdebug("flash access timeout");
				esas2r_write_register_dword(a, MU_DOORBELL_IN,
							    DRBL_FLASH_DONE);
				esas2r_enable_chip_interrupts(a);
			} else {
				esas2r_hdebug("flash release timeout");
			}

			return false;
		}
	}

	/* if we're done, re-enable chip interrupts */
	if (function == DRBL_FLASH_DONE)
		esas2r_enable_chip_interrupts(a);

	return true;
}