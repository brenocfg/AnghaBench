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
struct rpc_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,char const*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPCI_PROTOCOL_NUM ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 size_t max (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  vmw_close_channel (struct rpc_channel*) ; 
 int /*<<< orphan*/  vmw_msg_enabled ; 
 scalar_t__ vmw_open_channel (struct rpc_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ vmw_recv_msg (struct rpc_channel*,void*,size_t*) ; 
 scalar_t__ vmw_send_msg (struct rpc_channel*,char*) ; 

int vmw_host_get_guestinfo(const char *guest_info_param,
			   char *buffer, size_t *length)
{
	struct rpc_channel channel;
	char *msg, *reply = NULL;
	size_t reply_len = 0;

	if (!vmw_msg_enabled)
		return -ENODEV;

	if (!guest_info_param || !length)
		return -EINVAL;

	msg = kasprintf(GFP_KERNEL, "info-get %s", guest_info_param);
	if (!msg) {
		DRM_ERROR("Cannot allocate memory to get guest info \"%s\".",
			  guest_info_param);
		return -ENOMEM;
	}

	if (vmw_open_channel(&channel, RPCI_PROTOCOL_NUM))
		goto out_open;

	if (vmw_send_msg(&channel, msg) ||
	    vmw_recv_msg(&channel, (void *) &reply, &reply_len))
		goto out_msg;

	vmw_close_channel(&channel);
	if (buffer && reply && reply_len > 0) {
		/* Remove reply code, which are the first 2 characters of
		 * the reply
		 */
		reply_len = max(reply_len - 2, (size_t) 0);
		reply_len = min(reply_len, *length);

		if (reply_len > 0)
			memcpy(buffer, reply + 2, reply_len);
	}

	*length = reply_len;

	kfree(reply);
	kfree(msg);

	return 0;

out_msg:
	vmw_close_channel(&channel);
	kfree(reply);
out_open:
	*length = 0;
	kfree(msg);
	DRM_ERROR("Failed to get guest info \"%s\".", guest_info_param);

	return -EINVAL;
}