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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HIGH_WORD (unsigned long) ; 
 int MESSAGE_STATUS_CPT ; 
 int MESSAGE_STATUS_DORECV ; 
 int MESSAGE_STATUS_HB ; 
 int MESSAGE_STATUS_SUCCESS ; 
 int RETRIES ; 
 int /*<<< orphan*/  VMW_HYPERVISOR_MAGIC ; 
 int /*<<< orphan*/  VMW_PORT (int /*<<< orphan*/ ,int,unsigned long,unsigned long,int,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  VMW_PORT_CMD_RECVSIZE ; 
 int /*<<< orphan*/  VMW_PORT_CMD_RECVSTATUS ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 unsigned long vmw_port_hb_in (struct rpc_channel*,char*,size_t,int) ; 

__attribute__((used)) static int vmw_recv_msg(struct rpc_channel *channel, void **msg,
			size_t *msg_len)
{
	unsigned long eax, ebx, ecx, edx, si, di;
	char *reply;
	size_t reply_len;
	int retries = 0;


	*msg_len = 0;
	*msg = NULL;

	while (retries < RETRIES) {
		retries++;

		/* Set up additional parameters */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_RECVSIZE,
			0, si, di,
			channel->channel_id << 16,
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) {
			DRM_ERROR("Failed to get reply size for host message.\n");
			return -EINVAL;
		}

		/* No reply available.  This is okay. */
		if ((HIGH_WORD(ecx) & MESSAGE_STATUS_DORECV) == 0)
			return 0;

		reply_len = ebx;
		reply     = kzalloc(reply_len + 1, GFP_KERNEL);
		if (!reply) {
			DRM_ERROR("Cannot allocate memory for host message reply.\n");
			return -ENOMEM;
		}


		/* Receive buffer */
		ebx = vmw_port_hb_in(channel, reply, reply_len,
				     !!(HIGH_WORD(ecx) & MESSAGE_STATUS_HB));
		if ((HIGH_WORD(ebx) & MESSAGE_STATUS_SUCCESS) == 0) {
			kfree(reply);
			reply = NULL;
			if ((HIGH_WORD(ebx) & MESSAGE_STATUS_CPT) != 0) {
				/* A checkpoint occurred. Retry. */
				continue;
			}

			return -EINVAL;
		}

		reply[reply_len] = '\0';


		/* Ack buffer */
		si  = channel->cookie_high;
		di  = channel->cookie_low;

		VMW_PORT(VMW_PORT_CMD_RECVSTATUS,
			MESSAGE_STATUS_SUCCESS, si, di,
			channel->channel_id << 16,
			VMW_HYPERVISOR_MAGIC,
			eax, ebx, ecx, edx, si, di);

		if ((HIGH_WORD(ecx) & MESSAGE_STATUS_SUCCESS) == 0) {
			kfree(reply);
			reply = NULL;
			if ((HIGH_WORD(ecx) & MESSAGE_STATUS_CPT) != 0) {
				/* A checkpoint occurred. Retry. */
				continue;
			}

			return -EINVAL;
		}

		break;
	}

	if (!reply)
		return -EINVAL;

	*msg_len = reply_len;
	*msg     = reply;

	return 0;
}