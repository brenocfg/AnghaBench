#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct pdp_ctx {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_portid; TYPE_1__* nlhdr; int /*<<< orphan*/  snd_seq; int /*<<< orphan*/ * attrs; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 size_t GTPA_VERSION ; 
 scalar_t__ IS_ERR (struct pdp_ctx*) ; 
 TYPE_2__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 int PTR_ERR (struct pdp_ctx*) ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int genlmsg_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct pdp_ctx* gtp_find_pdp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int gtp_genl_fill_info (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pdp_ctx*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtp_genl_get_pdp(struct sk_buff *skb, struct genl_info *info)
{
	struct pdp_ctx *pctx = NULL;
	struct sk_buff *skb2;
	int err;

	if (!info->attrs[GTPA_VERSION])
		return -EINVAL;

	rcu_read_lock();

	pctx = gtp_find_pdp(sock_net(skb->sk), info->attrs);
	if (IS_ERR(pctx)) {
		err = PTR_ERR(pctx);
		goto err_unlock;
	}

	skb2 = genlmsg_new(NLMSG_GOODSIZE, GFP_ATOMIC);
	if (skb2 == NULL) {
		err = -ENOMEM;
		goto err_unlock;
	}

	err = gtp_genl_fill_info(skb2, NETLINK_CB(skb).portid,
				 info->snd_seq, info->nlhdr->nlmsg_type, pctx);
	if (err < 0)
		goto err_unlock_free;

	rcu_read_unlock();
	return genlmsg_unicast(genl_info_net(info), skb2, info->snd_portid);

err_unlock_free:
	kfree_skb(skb2);
err_unlock:
	rcu_read_unlock();
	return err;
}