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
struct rpc_channel {int channel_id; unsigned long cookie_high; unsigned long cookie_low; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int GUESTMSG_FLAG_COOKIE ; 
 int HIGH_WORD (unsigned long) ; 
 int MESSAGE_STATUS_SUCCESS ; 
 int /*<<< orphan*/  VMW_HYPERVISOR_MAGIC ; 
 int /*<<< orphan*/  VMW_PORT (int /*<<< orphan*/ ,unsigned int,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VMW_PORT_CMD_OPEN_CHANNEL ; 

__attribute__((used)) static int vmw_open_channel(struct rpc_channel *channel, unsigned int protocol)
{
	unsigned long eax, ebx, ecx, edx, si = 0, di = 0;

	VMW_PORT(VMW_PORT_CMD_OPEN_CHANNEL,
		(protocol | GUESTMSG_FLAG_COOKIE), si, di,
		0,
		VMW_HYPERVISOR_MAGIC,
		eax, ebx, ecx, edx, si, di);

	if ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0)
		return -EINVAL;

	channel->channel_id  = HIGH_WORD(edx);
	channel->cookie_high = si;
	channel->cookie_low  = di;

	return 0;
}