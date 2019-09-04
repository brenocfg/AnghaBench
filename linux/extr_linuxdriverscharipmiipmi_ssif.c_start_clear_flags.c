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
struct ssif_info {unsigned char msg_flags; int /*<<< orphan*/  ssif_state; } ;

/* Variables and functions */
 unsigned char IPMI_CLEAR_MSG_FLAGS_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  SSIF_CLEARING_FLAGS ; 
 int /*<<< orphan*/  SSIF_NORMAL ; 
 unsigned char WDT_PRE_TIMEOUT_INT ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 
 scalar_t__ start_send (struct ssif_info*,unsigned char*,int) ; 

__attribute__((used)) static void start_clear_flags(struct ssif_info *ssif_info, unsigned long *flags)
{
	unsigned char msg[3];

	ssif_info->msg_flags &= ~WDT_PRE_TIMEOUT_INT;
	ssif_info->ssif_state = SSIF_CLEARING_FLAGS;
	ipmi_ssif_unlock_cond(ssif_info, flags);

	/* Make sure the watchdog pre-timeout flag is not set at startup. */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;

	if (start_send(ssif_info, msg, 3) != 0) {
		/* Error, just go to normal state. */
		ssif_info->ssif_state = SSIF_NORMAL;
	}
}