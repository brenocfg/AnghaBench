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
union xpc_channel_ctl_flags {int* flags; } ;

/* Variables and functions */
 int XPC_MAX_NCHANNELS ; 
 int XPC_MSG_CHCTL_FLAGS ; 

__attribute__((used)) static inline int
xpc_any_msg_chctl_flags_set(union xpc_channel_ctl_flags *chctl)
{
	int ch_number;

	for (ch_number = 0; ch_number < XPC_MAX_NCHANNELS; ch_number++) {
		if (chctl->flags[ch_number] & XPC_MSG_CHCTL_FLAGS)
			return 1;
	}
	return 0;
}