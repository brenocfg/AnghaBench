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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct gtp_dev {struct sock* sk1u; struct sock* sk0; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t GTPA_FLOW ; 
 size_t GTPA_I_TEI ; 
 size_t GTPA_LINK ; 
 size_t GTPA_MS_ADDRESS ; 
 size_t GTPA_O_TEI ; 
 size_t GTPA_PEER_ADDRESS ; 
 size_t GTPA_TID ; 
 size_t GTPA_VERSION ; 
#define  GTP_V0 129 
#define  GTP_V1 128 
 struct gtp_dev* gtp_find_dev (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ipv4_pdp_add (struct gtp_dev*,struct sock*,struct genl_info*) ; 
 unsigned int nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gtp_genl_new_pdp(struct sk_buff *skb, struct genl_info *info)
{
	unsigned int version;
	struct gtp_dev *gtp;
	struct sock *sk;
	int err;

	if (!info->attrs[GTPA_VERSION] ||
	    !info->attrs[GTPA_LINK] ||
	    !info->attrs[GTPA_PEER_ADDRESS] ||
	    !info->attrs[GTPA_MS_ADDRESS])
		return -EINVAL;

	version = nla_get_u32(info->attrs[GTPA_VERSION]);

	switch (version) {
	case GTP_V0:
		if (!info->attrs[GTPA_TID] ||
		    !info->attrs[GTPA_FLOW])
			return -EINVAL;
		break;
	case GTP_V1:
		if (!info->attrs[GTPA_I_TEI] ||
		    !info->attrs[GTPA_O_TEI])
			return -EINVAL;
		break;

	default:
		return -EINVAL;
	}

	rtnl_lock();
	rcu_read_lock();

	gtp = gtp_find_dev(sock_net(skb->sk), info->attrs);
	if (!gtp) {
		err = -ENODEV;
		goto out_unlock;
	}

	if (version == GTP_V0)
		sk = gtp->sk0;
	else if (version == GTP_V1)
		sk = gtp->sk1u;
	else
		sk = NULL;

	if (!sk) {
		err = -ENODEV;
		goto out_unlock;
	}

	err = ipv4_pdp_add(gtp, sk, info);

out_unlock:
	rcu_read_unlock();
	rtnl_unlock();
	return err;
}