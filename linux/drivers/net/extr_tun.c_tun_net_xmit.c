#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tun_struct {TYPE_2__* pcpu_stats; int /*<<< orphan*/  txflt; int /*<<< orphan*/  steering_prog; int /*<<< orphan*/ * tfiles; } ;
struct TYPE_5__ {TYPE_3__* sk; } ;
struct tun_file {int flags; TYPE_1__ socket; int /*<<< orphan*/  fasync; int /*<<< orphan*/  tx_ring; } ;
struct sk_buff {int queue_mapping; int len; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* sk_data_ready ) (TYPE_3__*) ;scalar_t__ sk_filter; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  NET_XMIT_DROP ; 
 int /*<<< orphan*/  POLL_IN ; 
 int /*<<< orphan*/  SIGIO ; 
 int TUN_FASYNC ; 
 int /*<<< orphan*/  check_filter (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nf_reset_ct (struct sk_buff*) ; 
 scalar_t__ pskb_trim (struct sk_buff*,int) ; 
 scalar_t__ ptr_ring_produce (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct tun_file* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int run_ebpf_filter (struct tun_struct*,struct sk_buff*,int) ; 
 scalar_t__ sk_filter (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan_frags_rx (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_tx_error (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tun_automq_xmit (struct tun_struct*,struct sk_buff*) ; 
 int /*<<< orphan*/  tun_debug (int /*<<< orphan*/ ,struct tun_struct*,char*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t tun_net_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);
	int txq = skb->queue_mapping;
	struct tun_file *tfile;
	int len = skb->len;

	rcu_read_lock();
	tfile = rcu_dereference(tun->tfiles[txq]);

	/* Drop packet if interface is not attached */
	if (!tfile)
		goto drop;

	if (!rcu_dereference(tun->steering_prog))
		tun_automq_xmit(tun, skb);

	tun_debug(KERN_INFO, tun, "tun_net_xmit %d\n", skb->len);

	BUG_ON(!tfile);

	/* Drop if the filter does not like it.
	 * This is a noop if the filter is disabled.
	 * Filter can be enabled only for the TAP devices. */
	if (!check_filter(&tun->txflt, skb))
		goto drop;

	if (tfile->socket.sk->sk_filter &&
	    sk_filter(tfile->socket.sk, skb))
		goto drop;

	len = run_ebpf_filter(tun, skb, len);
	if (len == 0 || pskb_trim(skb, len))
		goto drop;

	if (unlikely(skb_orphan_frags_rx(skb, GFP_ATOMIC)))
		goto drop;

	skb_tx_timestamp(skb);

	/* Orphan the skb - required as we might hang on to it
	 * for indefinite time.
	 */
	skb_orphan(skb);

	nf_reset_ct(skb);

	if (ptr_ring_produce(&tfile->tx_ring, skb))
		goto drop;

	/* Notify and wake up reader process */
	if (tfile->flags & TUN_FASYNC)
		kill_fasync(&tfile->fasync, SIGIO, POLL_IN);
	tfile->socket.sk->sk_data_ready(tfile->socket.sk);

	rcu_read_unlock();
	return NETDEV_TX_OK;

drop:
	this_cpu_inc(tun->pcpu_stats->tx_dropped);
	skb_tx_error(skb);
	kfree_skb(skb);
	rcu_read_unlock();
	return NET_XMIT_DROP;
}