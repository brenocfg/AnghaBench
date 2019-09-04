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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct skb_shared_hwtstamps {int /*<<< orphan*/  hwtstamp; } ;
struct sk_buff {unsigned int len; int /*<<< orphan*/  protocol; } ;
struct rtnl_link_stats64 {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_errors; } ;
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;
typedef  struct qm_fd {int status; int /*<<< orphan*/  bpid; } const qm_fd ;
struct qm_dqrr_entry {struct qm_fd const fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct net_device {int features; TYPE_1__ dev; } ;
struct dpaa_priv {TYPE_2__* mac_dev; scalar_t__ keygen_in_use; scalar_t__ rx_tstamp; int /*<<< orphan*/  percpu_priv; } ;
struct dpaa_percpu_priv {struct rtnl_link_stats64 stats; } ;
struct dpaa_fq {struct net_device* net_dev; } ;
struct dpaa_bp {int /*<<< orphan*/  percpu_count; int /*<<< orphan*/  size; int /*<<< orphan*/  dev; } ;
typedef  enum qman_cb_dqrr_result { ____Placeholder_qman_cb_dqrr_result } qman_cb_dqrr_result ;
typedef  enum qm_fd_format { ____Placeholder_qm_fd_format } qm_fd_format ;
typedef  enum pkt_hash_types { ____Placeholder_pkt_hash_types } pkt_hash_types ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/ * port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int FM_FD_STAT_L4CV ; 
 int FM_FD_STAT_RX_ERRORS ; 
 int NETIF_F_RXHASH ; 
 scalar_t__ NET_RX_DROP ; 
 int PKT_HASH_TYPE_L3 ; 
 int PKT_HASH_TYPE_L4 ; 
 size_t RX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int be32_to_cpu (int) ; 
 struct sk_buff* contig_fd_to_skb (struct dpaa_priv*,struct qm_fd const*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dpaa_bp* dpaa_bpid2pool (int /*<<< orphan*/ ) ; 
 int dpaa_eth_napi_schedule (struct dpaa_percpu_priv*,struct qman_portal*) ; 
 int dpaa_eth_refill_bpools (struct dpaa_priv*) ; 
 int /*<<< orphan*/  dpaa_fd_release (struct net_device*,struct qm_fd const*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  fman_port_get_hash_result_offset (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  fman_port_get_tstamp (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memset (struct skb_shared_hwtstamps*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ net_ratelimit () ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_warn (struct dpaa_priv*,int /*<<< orphan*/ ,struct net_device*,char*,int) ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  qm_fd_addr (struct qm_fd const*) ; 
 int qm_fd_contig ; 
 int qm_fd_get_format (struct qm_fd const*) ; 
 int qm_fd_get_offset (struct qm_fd const*) ; 
 int qm_fd_sg ; 
 int qman_cb_dqrr_consume ; 
 int qman_cb_dqrr_stop ; 
 struct sk_buff* sg_fd_to_skb (struct dpaa_priv*,struct qm_fd const*) ; 
 struct skb_shared_hwtstamps* skb_hwtstamps (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_set_hash (struct sk_buff*,int,int) ; 
 void* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpaa_rx_fd (struct net_device*,struct qman_fq*,struct qm_fd const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static enum qman_cb_dqrr_result rx_default_dqrr(struct qman_portal *portal,
						struct qman_fq *fq,
						const struct qm_dqrr_entry *dq)
{
	struct skb_shared_hwtstamps *shhwtstamps;
	struct rtnl_link_stats64 *percpu_stats;
	struct dpaa_percpu_priv *percpu_priv;
	const struct qm_fd *fd = &dq->fd;
	dma_addr_t addr = qm_fd_addr(fd);
	enum qm_fd_format fd_format;
	struct net_device *net_dev;
	u32 fd_status, hash_offset;
	struct dpaa_bp *dpaa_bp;
	struct dpaa_priv *priv;
	unsigned int skb_len;
	struct sk_buff *skb;
	int *count_ptr;
	void *vaddr;
	u64 ns;

	fd_status = be32_to_cpu(fd->status);
	fd_format = qm_fd_get_format(fd);
	net_dev = ((struct dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);
	dpaa_bp = dpaa_bpid2pool(dq->fd.bpid);
	if (!dpaa_bp)
		return qman_cb_dqrr_consume;

	/* Trace the Rx fd */
	trace_dpaa_rx_fd(net_dev, fq, &dq->fd);

	percpu_priv = this_cpu_ptr(priv->percpu_priv);
	percpu_stats = &percpu_priv->stats;

	if (unlikely(dpaa_eth_napi_schedule(percpu_priv, portal)))
		return qman_cb_dqrr_stop;

	/* Make sure we didn't run out of buffers */
	if (unlikely(dpaa_eth_refill_bpools(priv))) {
		/* Unable to refill the buffer pool due to insufficient
		 * system memory. Just release the frame back into the pool,
		 * otherwise we'll soon end up with an empty buffer pool.
		 */
		dpaa_fd_release(net_dev, &dq->fd);
		return qman_cb_dqrr_consume;
	}

	if (unlikely(fd_status & FM_FD_STAT_RX_ERRORS) != 0) {
		if (net_ratelimit())
			netif_warn(priv, hw, net_dev, "FD status = 0x%08x\n",
				   fd_status & FM_FD_STAT_RX_ERRORS);

		percpu_stats->rx_errors++;
		dpaa_fd_release(net_dev, fd);
		return qman_cb_dqrr_consume;
	}

	dpaa_bp = dpaa_bpid2pool(fd->bpid);
	if (!dpaa_bp)
		return qman_cb_dqrr_consume;

	dma_unmap_single(dpaa_bp->dev, addr, dpaa_bp->size, DMA_FROM_DEVICE);

	/* prefetch the first 64 bytes of the frame or the SGT start */
	vaddr = phys_to_virt(addr);
	prefetch(vaddr + qm_fd_get_offset(fd));

	/* The only FD types that we may receive are contig and S/G */
	WARN_ON((fd_format != qm_fd_contig) && (fd_format != qm_fd_sg));

	/* Account for either the contig buffer or the SGT buffer (depending on
	 * which case we were in) having been removed from the pool.
	 */
	count_ptr = this_cpu_ptr(dpaa_bp->percpu_count);
	(*count_ptr)--;

	if (likely(fd_format == qm_fd_contig))
		skb = contig_fd_to_skb(priv, fd);
	else
		skb = sg_fd_to_skb(priv, fd);
	if (!skb)
		return qman_cb_dqrr_consume;

	if (priv->rx_tstamp) {
		shhwtstamps = skb_hwtstamps(skb);
		memset(shhwtstamps, 0, sizeof(*shhwtstamps));

		if (!fman_port_get_tstamp(priv->mac_dev->port[RX], vaddr, &ns))
			shhwtstamps->hwtstamp = ns_to_ktime(ns);
		else
			dev_warn(net_dev->dev.parent, "fman_port_get_tstamp failed!\n");
	}

	skb->protocol = eth_type_trans(skb, net_dev);

	if (net_dev->features & NETIF_F_RXHASH && priv->keygen_in_use &&
	    !fman_port_get_hash_result_offset(priv->mac_dev->port[RX],
					      &hash_offset)) {
		enum pkt_hash_types type;

		/* if L4 exists, it was used in the hash generation */
		type = be32_to_cpu(fd->status) & FM_FD_STAT_L4CV ?
			PKT_HASH_TYPE_L4 : PKT_HASH_TYPE_L3;
		skb_set_hash(skb, be32_to_cpu(*(u32 *)(vaddr + hash_offset)),
			     type);
	}

	skb_len = skb->len;

	if (unlikely(netif_receive_skb(skb) == NET_RX_DROP)) {
		percpu_stats->rx_dropped++;
		return qman_cb_dqrr_consume;
	}

	percpu_stats->rx_packets++;
	percpu_stats->rx_bytes += skb_len;

	return qman_cb_dqrr_consume;
}