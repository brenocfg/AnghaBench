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
struct tcmu_dev {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  enum tcmu_genl_cmd { ____Placeholder_tcmu_genl_cmd } tcmu_genl_cmd ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TCMU_CMD_ADDED_DEVICE ; 
 int /*<<< orphan*/  TCMU_MCGRP_CONFIG ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_multicast_allns (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 int /*<<< orphan*/  tcmu_destroy_genl_cmd_reply (struct tcmu_dev*) ; 
 int /*<<< orphan*/  tcmu_genl_family ; 
 int tcmu_init_genl_cmd_reply (struct tcmu_dev*,int) ; 
 int tcmu_wait_genl_cmd_reply (struct tcmu_dev*) ; 

__attribute__((used)) static int tcmu_netlink_event_send(struct tcmu_dev *udev,
				   enum tcmu_genl_cmd cmd,
				   struct sk_buff *skb, void *msg_header)
{
	int ret;

	genlmsg_end(skb, msg_header);

	ret = tcmu_init_genl_cmd_reply(udev, cmd);
	if (ret) {
		nlmsg_free(skb);
		return ret;
	}

	ret = genlmsg_multicast_allns(&tcmu_genl_family, skb, 0,
				      TCMU_MCGRP_CONFIG, GFP_KERNEL);

	/* Wait during an add as the listener may not be up yet */
	if (ret == 0 ||
	   (ret == -ESRCH && cmd == TCMU_CMD_ADDED_DEVICE))
		return tcmu_wait_genl_cmd_reply(udev);
	else
		tcmu_destroy_genl_cmd_reply(udev);

	return ret;
}