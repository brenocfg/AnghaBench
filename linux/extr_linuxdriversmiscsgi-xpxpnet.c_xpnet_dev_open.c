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
struct net_device {int /*<<< orphan*/  name; } ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  XPC_NET_CHANNEL ; 
 scalar_t__ XPNET_MAX_IDLE_KTHREADS ; 
 scalar_t__ XPNET_MAX_KTHREADS ; 
 scalar_t__ XPNET_MSG_NENTRIES ; 
 scalar_t__ XPNET_MSG_SIZE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int xpSuccess ; 
 int xpc_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  xpnet ; 
 int /*<<< orphan*/  xpnet_connection_activity ; 

__attribute__((used)) static int
xpnet_dev_open(struct net_device *dev)
{
	enum xp_retval ret;

	dev_dbg(xpnet, "calling xpc_connect(%d, 0x%p, NULL, %ld, %ld, %ld, "
		"%ld)\n", XPC_NET_CHANNEL, xpnet_connection_activity,
		(unsigned long)XPNET_MSG_SIZE,
		(unsigned long)XPNET_MSG_NENTRIES,
		(unsigned long)XPNET_MAX_KTHREADS,
		(unsigned long)XPNET_MAX_IDLE_KTHREADS);

	ret = xpc_connect(XPC_NET_CHANNEL, xpnet_connection_activity, NULL,
			  XPNET_MSG_SIZE, XPNET_MSG_NENTRIES,
			  XPNET_MAX_KTHREADS, XPNET_MAX_IDLE_KTHREADS);
	if (ret != xpSuccess) {
		dev_err(xpnet, "ifconfig up of %s failed on XPC connect, "
			"ret=%d\n", dev->name, ret);

		return -ENOMEM;
	}

	dev_dbg(xpnet, "ifconfig up of %s; XPC connected\n", dev->name);

	return 0;
}