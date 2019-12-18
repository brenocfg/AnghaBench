#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct virtproc_info {TYPE_1__* vdev; } ;
struct rpmsg_ns_msg {char* name; int flags; int /*<<< orphan*/  addr; } ;
struct rpmsg_device {int dummy; } ;
struct rpmsg_channel_info {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  RPMSG_ADDR_ANY ; 
 int RPMSG_NAME_SIZE ; 
 int RPMSG_NS_DESTROY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_hex_dump (char*,int /*<<< orphan*/ ,int,int,void*,int,int) ; 
 struct rpmsg_device* rpmsg_create_channel (struct virtproc_info*,struct rpmsg_channel_info*) ; 
 int rpmsg_unregister_device (struct device*,struct rpmsg_channel_info*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int rpmsg_ns_cb(struct rpmsg_device *rpdev, void *data, int len,
		       void *priv, u32 src)
{
	struct rpmsg_ns_msg *msg = data;
	struct rpmsg_device *newch;
	struct rpmsg_channel_info chinfo;
	struct virtproc_info *vrp = priv;
	struct device *dev = &vrp->vdev->dev;
	int ret;

#if defined(CONFIG_DYNAMIC_DEBUG)
	dynamic_hex_dump("NS announcement: ", DUMP_PREFIX_NONE, 16, 1,
			 data, len, true);
#endif

	if (len != sizeof(*msg)) {
		dev_err(dev, "malformed ns msg (%d)\n", len);
		return -EINVAL;
	}

	/*
	 * the name service ept does _not_ belong to a real rpmsg channel,
	 * and is handled by the rpmsg bus itself.
	 * for sanity reasons, make sure a valid rpdev has _not_ sneaked
	 * in somehow.
	 */
	if (rpdev) {
		dev_err(dev, "anomaly: ns ept has an rpdev handle\n");
		return -EINVAL;
	}

	/* don't trust the remote processor for null terminating the name */
	msg->name[RPMSG_NAME_SIZE - 1] = '\0';

	dev_info(dev, "%sing channel %s addr 0x%x\n",
		 msg->flags & RPMSG_NS_DESTROY ? "destroy" : "creat",
		 msg->name, msg->addr);

	strncpy(chinfo.name, msg->name, sizeof(chinfo.name));
	chinfo.src = RPMSG_ADDR_ANY;
	chinfo.dst = msg->addr;

	if (msg->flags & RPMSG_NS_DESTROY) {
		ret = rpmsg_unregister_device(&vrp->vdev->dev, &chinfo);
		if (ret)
			dev_err(dev, "rpmsg_destroy_channel failed: %d\n", ret);
	} else {
		newch = rpmsg_create_channel(vrp, &chinfo);
		if (!newch)
			dev_err(dev, "rpmsg_create_channel failed\n");
	}

	return 0;
}