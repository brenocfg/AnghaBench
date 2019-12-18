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
typedef  scalar_t__ u32 ;
struct cnic_sock {scalar_t__ state; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ L4_KCQE_OPCODE_VALUE_CLOSE_COMP ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_COMP ; 
 scalar_t__ L4_KCQE_OPCODE_VALUE_RESET_RECEIVED ; 
 int /*<<< orphan*/  SK_F_CLOSING ; 
 int /*<<< orphan*/  SK_F_OFFLD_COMPLETE ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cnic_ready_to_close(struct cnic_sock *csk, u32 opcode)
{
	if (test_and_clear_bit(SK_F_OFFLD_COMPLETE, &csk->flags)) {
		/* Unsolicited RESET_COMP or RESET_RECEIVED */
		opcode = L4_KCQE_OPCODE_VALUE_RESET_RECEIVED;
		csk->state = opcode;
	}

	/* 1. If event opcode matches the expected event in csk->state
	 * 2. If the expected event is CLOSE_COMP or RESET_COMP, we accept any
	 *    event
	 * 3. If the expected event is 0, meaning the connection was never
	 *    never established, we accept the opcode from cm_abort.
	 */
	if (opcode == csk->state || csk->state == 0 ||
	    csk->state == L4_KCQE_OPCODE_VALUE_CLOSE_COMP ||
	    csk->state == L4_KCQE_OPCODE_VALUE_RESET_COMP) {
		if (!test_and_set_bit(SK_F_CLOSING, &csk->flags)) {
			if (csk->state == 0)
				csk->state = opcode;
			return 1;
		}
	}
	return 0;
}