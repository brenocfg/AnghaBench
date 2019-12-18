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
struct sk_buff {int dummy; } ;
struct hwsim_phy {int dummy; } ;
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAC802154_HWSIM_CMD_NEW_RADIO ; 
 scalar_t__ append_radio_msg (struct sk_buff*,struct hwsim_phy*) ; 
 int /*<<< orphan*/  genlmsg_cancel (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwsim_genl_family ; 
 int /*<<< orphan*/  hwsim_mcast_config_msg (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static void hwsim_mcast_new_radio(struct genl_info *info, struct hwsim_phy *phy)
{
	struct sk_buff *mcast_skb;
	void *data;

	mcast_skb = genlmsg_new(GENLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!mcast_skb)
		return;

	data = genlmsg_put(mcast_skb, 0, 0, &hwsim_genl_family, 0,
			   MAC802154_HWSIM_CMD_NEW_RADIO);
	if (!data)
		goto out_err;

	if (append_radio_msg(mcast_skb, phy) < 0)
		goto out_err;

	genlmsg_end(mcast_skb, data);

	hwsim_mcast_config_msg(mcast_skb, info);
	return;

out_err:
	genlmsg_cancel(mcast_skb, data);
	nlmsg_free(mcast_skb);
}