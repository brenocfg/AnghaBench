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
struct rpc_channel {unsigned long cookie_high; unsigned long cookie_low; int channel_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int HIGH_WORD (unsigned long) ; 
 int MESSAGE_STATUS_CPT ; 
 int MESSAGE_STATUS_HB ; 
 int MESSAGE_STATUS_SUCCESS ; 
 int RETRIES ; 
 int VMW_HYPERVISOR_HB_PORT ; 
 int /*<<< orphan*/  VMW_HYPERVISOR_MAGIC ; 
 int VMW_HYPERVISOR_PORT ; 
 int /*<<< orphan*/  VMW_PORT (int /*<<< orphan*/ ,size_t,unsigned long,unsigned long,int,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int VMW_PORT_CMD_HB_MSG ; 
 int /*<<< orphan*/  VMW_PORT_CMD_SENDSIZE ; 
 int /*<<< orphan*/  VMW_PORT_HB_OUT (int,size_t,unsigned long,unsigned long,int,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int vmw_send_msg(struct rpc_channel *channel, const char *msg)
{
	unsigned long eax, ebx, ecx, edx, si, di, bp;
	size_t msg_len = strlen(msg);
	int retries = 0;


	while (retries < RETRIES) {
		retries++;

		/* Set up additional parameters */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_SENDSIZE,
			msg_len, si, di,
			VMW_HYPERVISOR_PORT | (channel->channel_id << 16),
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0 ||
		    (HIGH_WORD(ecx) & MESSAGE_STATUS_HB) == 0) {
			/* Expected success + high-bandwidth. Give up. */
			return -EINVAL;
		}

		/* Send msg */
		si  = (uintptr_t) msg;
		di  = channel->cookie_low;
		bp  = channel->cookie_high;

		VMW_PORT_HB_OUT(
			(MESSAGE_STATUS_SUCCESS << 16) | VMW_PORT_CMD_HB_MSG,
			msg_len, si, di,
			VMW_HYPERVISOR_HB_PORT | (channel->channel_id << 16),
			VMW_HYPERVISOR_MAGIC, bp,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WORD(ebx) & MESSAGE_STATUS_SUCCESS) != 0) {
			return 0;
		} else if ((HIGH_WORD(ebx) & MESSAGE_STATUS_CPT) != 0) {
			/* A checkpoint occurred. Retry. */
			continue;
		} else {
			break;
		}
	}

	return -EINVAL;
}