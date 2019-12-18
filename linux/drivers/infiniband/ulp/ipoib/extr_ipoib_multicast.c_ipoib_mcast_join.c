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
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sl; int /*<<< orphan*/  rate; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  mtu; int /*<<< orphan*/  qkey; TYPE_1__ mgid; } ;
struct ipoib_mcast {int /*<<< orphan*/  done; int /*<<< orphan*/  flags; TYPE_2__ mcmember; } ;
struct ipoib_dev_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  port; int /*<<< orphan*/  ca; scalar_t__ sm_fullmember_sendonly_support; struct ipoib_mcast* broadcast; int /*<<< orphan*/  pkey; int /*<<< orphan*/  local_gid; int /*<<< orphan*/  flags; } ;
struct ib_sa_multicast {int dummy; } ;
struct ib_sa_mcmember_rec {int join_state; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  sl; int /*<<< orphan*/  rate; void* rate_selector; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  mtu; void* mtu_selector; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey; int /*<<< orphan*/  port_gid; TYPE_1__ mgid; } ;
typedef  int ib_sa_comp_mask ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* IB_SA_EQ ; 
 int IB_SA_MCMEMBER_REC_FLOW_LABEL ; 
 int IB_SA_MCMEMBER_REC_HOP_LIMIT ; 
 int IB_SA_MCMEMBER_REC_JOIN_STATE ; 
 int IB_SA_MCMEMBER_REC_MGID ; 
 int IB_SA_MCMEMBER_REC_MTU ; 
 int IB_SA_MCMEMBER_REC_MTU_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_PKEY ; 
 int IB_SA_MCMEMBER_REC_PORT_GID ; 
 int IB_SA_MCMEMBER_REC_QKEY ; 
 int IB_SA_MCMEMBER_REC_RATE ; 
 int IB_SA_MCMEMBER_REC_RATE_SELECTOR ; 
 int IB_SA_MCMEMBER_REC_SL ; 
 int IB_SA_MCMEMBER_REC_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IPOIB_FLAG_OPER_UP ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_BUSY ; 
 int /*<<< orphan*/  IPOIB_MCAST_FLAG_SENDONLY ; 
 scalar_t__ IS_ERR (struct ib_sa_multicast*) ; 
 int PTR_ERR (struct ib_sa_multicast*) ; 
 int SENDONLY_FULLMEMBER_JOIN ; 
 int /*<<< orphan*/  __ipoib_mcast_schedule_join_thread (struct ipoib_dev_priv*,struct ipoib_mcast*,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 struct ib_sa_multicast* ib_sa_join_multicast (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ib_sa_mcmember_rec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ipoib_mcast*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_dbg_mcast (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_mcast_join_complete ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_sa_client ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipoib_mcast_join(struct net_device *dev, struct ipoib_mcast *mcast)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	struct ib_sa_multicast *multicast;
	struct ib_sa_mcmember_rec rec = {
		.join_state = 1
	};
	ib_sa_comp_mask comp_mask;
	int ret = 0;

	if (!priv->broadcast ||
	    !test_bit(IPOIB_FLAG_OPER_UP, &priv->flags))
		return -EINVAL;

	init_completion(&mcast->done);
	set_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);

	ipoib_dbg_mcast(priv, "joining MGID %pI6\n", mcast->mcmember.mgid.raw);

	rec.mgid     = mcast->mcmember.mgid;
	rec.port_gid = priv->local_gid;
	rec.pkey     = cpu_to_be16(priv->pkey);

	comp_mask =
		IB_SA_MCMEMBER_REC_MGID		|
		IB_SA_MCMEMBER_REC_PORT_GID	|
		IB_SA_MCMEMBER_REC_PKEY		|
		IB_SA_MCMEMBER_REC_JOIN_STATE;

	if (mcast != priv->broadcast) {
		/*
		 * RFC 4391:
		 *  The MGID MUST use the same P_Key, Q_Key, SL, MTU,
		 *  and HopLimit as those used in the broadcast-GID.  The rest
		 *  of attributes SHOULD follow the values used in the
		 *  broadcast-GID as well.
		 */
		comp_mask |=
			IB_SA_MCMEMBER_REC_QKEY			|
			IB_SA_MCMEMBER_REC_MTU_SELECTOR		|
			IB_SA_MCMEMBER_REC_MTU			|
			IB_SA_MCMEMBER_REC_TRAFFIC_CLASS	|
			IB_SA_MCMEMBER_REC_RATE_SELECTOR	|
			IB_SA_MCMEMBER_REC_RATE			|
			IB_SA_MCMEMBER_REC_SL			|
			IB_SA_MCMEMBER_REC_FLOW_LABEL		|
			IB_SA_MCMEMBER_REC_HOP_LIMIT;

		rec.qkey	  = priv->broadcast->mcmember.qkey;
		rec.mtu_selector  = IB_SA_EQ;
		rec.mtu		  = priv->broadcast->mcmember.mtu;
		rec.traffic_class = priv->broadcast->mcmember.traffic_class;
		rec.rate_selector = IB_SA_EQ;
		rec.rate	  = priv->broadcast->mcmember.rate;
		rec.sl		  = priv->broadcast->mcmember.sl;
		rec.flow_label	  = priv->broadcast->mcmember.flow_label;
		rec.hop_limit	  = priv->broadcast->mcmember.hop_limit;

		/*
		 * Send-only IB Multicast joins work at the core IB layer but
		 * require specific SM support.
		 * We can use such joins here only if the current SM supports that feature.
		 * However, if not, we emulate an Ethernet multicast send,
		 * which does not require a multicast subscription and will
		 * still send properly. The most appropriate thing to
		 * do is to create the group if it doesn't exist as that
		 * most closely emulates the behavior, from a user space
		 * application perspective, of Ethernet multicast operation.
		 */
		if (test_bit(IPOIB_MCAST_FLAG_SENDONLY, &mcast->flags) &&
		    priv->sm_fullmember_sendonly_support)
			/* SM supports sendonly-fullmember, otherwise fallback to full-member */
			rec.join_state = SENDONLY_FULLMEMBER_JOIN;
	}
	spin_unlock_irq(&priv->lock);

	multicast = ib_sa_join_multicast(&ipoib_sa_client, priv->ca, priv->port,
					 &rec, comp_mask, GFP_KERNEL,
					 ipoib_mcast_join_complete, mcast);
	spin_lock_irq(&priv->lock);
	if (IS_ERR(multicast)) {
		ret = PTR_ERR(multicast);
		ipoib_warn(priv, "ib_sa_join_multicast failed, status %d\n", ret);
		/* Requeue this join task with a backoff delay */
		__ipoib_mcast_schedule_join_thread(priv, mcast, 1);
		clear_bit(IPOIB_MCAST_FLAG_BUSY, &mcast->flags);
		spin_unlock_irq(&priv->lock);
		complete(&mcast->done);
		spin_lock_irq(&priv->lock);
	}
	return 0;
}