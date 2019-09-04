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
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RPCI_PROTOCOL_NUM ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  vmw_close_channel (struct rpc_channel*) ; 
 int /*<<< orphan*/  vmw_msg_enabled ; 
 scalar_t__ vmw_open_channel (struct rpc_channel*,int /*<<< orphan*/ ) ; 
 scalar_t__ vmw_send_msg (struct rpc_channel*,char*) ; 

int vmw_host_log(const char *log)
{
	struct rpc_channel channel;
	char *msg;
	int ret = 0;


	if (!vmw_msg_enabled)
		return -ENODEV;

	if (!log)
		return ret;

	msg = kasprintf(GFP_KERNEL, "log %s", log);
	if (!msg) {
		DRM_ERROR("Cannot allocate memory for host log message.\n");
		return -ENOMEM;
	}

	if (vmw_open_channel(&channel, RPCI_PROTOCOL_NUM))
		goto out_open;

	if (vmw_send_msg(&channel, msg))
		goto out_msg;

	vmw_close_channel(&channel);
	kfree(msg);

	return 0;

out_msg:
	vmw_close_channel(&channel);
out_open:
	kfree(msg);
	DRM_ERROR("Failed to send host log message.\n");

	return -EINVAL;
}