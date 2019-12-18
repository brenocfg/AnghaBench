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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  ts ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct nicvf {int /*<<< orphan*/ * ptp_skb; int /*<<< orphan*/  ptp_clock; int /*<<< orphan*/  tx_ptp_skbs; struct nicvf* pnicvf; } ;
struct net_device {int dummy; } ;
struct cqe_send_t {scalar_t__ send_status; int /*<<< orphan*/  ptp_timestamp; } ;

/* Variables and functions */
 scalar_t__ CQ_TX_ERROP_TSTMP_CONFLICT ; 
 scalar_t__ CQ_TX_ERROP_TSTMP_TIMEOUT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cavium_ptp_tstamp2time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tstamp_tx (int /*<<< orphan*/ *,struct skb_shared_hwtstamps*) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void nicvf_snd_ptp_handler(struct net_device *netdev,
				  struct cqe_send_t *cqe_tx)
{
	struct nicvf *nic = netdev_priv(netdev);
	struct skb_shared_hwtstamps ts;
	u64 ns;

	nic = nic->pnicvf;

	/* Sync for 'ptp_skb' */
	smp_rmb();

	/* New timestamp request can be queued now */
	atomic_set(&nic->tx_ptp_skbs, 0);

	/* Check for timestamp requested skb */
	if (!nic->ptp_skb)
		return;

	/* Check if timestamping is timedout, which is set to 10us */
	if (cqe_tx->send_status == CQ_TX_ERROP_TSTMP_TIMEOUT ||
	    cqe_tx->send_status == CQ_TX_ERROP_TSTMP_CONFLICT)
		goto no_tstamp;

	/* Get the timestamp */
	memset(&ts, 0, sizeof(ts));
	ns = cavium_ptp_tstamp2time(nic->ptp_clock, cqe_tx->ptp_timestamp);
	ts.hwtstamp = ns_to_ktime(ns);
	skb_tstamp_tx(nic->ptp_skb, &ts);

no_tstamp:
	/* Free the original skb */
	dev_kfree_skb_any(nic->ptp_skb);
	nic->ptp_skb = NULL;
	/* Sync 'ptp_skb' */
	smp_wmb();
}