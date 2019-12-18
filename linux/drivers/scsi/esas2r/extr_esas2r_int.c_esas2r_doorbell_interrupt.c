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
struct esas2r_adapter {int /*<<< orphan*/  flags2; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_COREDUMP_AVAIL ; 
 int /*<<< orphan*/  AF_BUSRST_DETECTED ; 
 int /*<<< orphan*/  AF_HEARTBEAT ; 
 int DRBL_FORCE_INT ; 
 int DRBL_FW_RESET ; 
 int DRBL_PANIC_REASON_MASK ; 
 int DRBL_RESET_BUS ; 
 int /*<<< orphan*/  ESAS2R_LOG_CRIT ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_hdebug (char*) ; 
 int /*<<< orphan*/  esas2r_local_reset_adapter (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  esas2r_trace (char*,int) ; 
 int /*<<< orphan*/  esas2r_trace_enter () ; 
 int /*<<< orphan*/  esas2r_trace_exit () ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_doorbell_interrupt(struct esas2r_adapter *a, u32 doorbell)
{
	if (!(doorbell & DRBL_FORCE_INT)) {
		esas2r_trace_enter();
		esas2r_trace("doorbell: %x", doorbell);
	}

	/* First clear the doorbell bits */
	esas2r_write_register_dword(a, MU_DOORBELL_OUT, doorbell);

	if (doorbell & DRBL_RESET_BUS)
		set_bit(AF_BUSRST_DETECTED, &a->flags);

	if (doorbell & DRBL_FORCE_INT)
		clear_bit(AF_HEARTBEAT, &a->flags);

	if (doorbell & DRBL_PANIC_REASON_MASK) {
		esas2r_hdebug("*** Firmware Panic ***");
		esas2r_log(ESAS2R_LOG_CRIT, "The firmware has panicked");
	}

	if (doorbell & DRBL_FW_RESET) {
		set_bit(AF2_COREDUMP_AVAIL, &a->flags2);
		esas2r_local_reset_adapter(a);
	}

	if (!(doorbell & DRBL_FORCE_INT))
		esas2r_trace_exit();
}