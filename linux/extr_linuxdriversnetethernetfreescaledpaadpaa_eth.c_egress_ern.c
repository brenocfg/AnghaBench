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
struct qm_fd {int dummy; } ;
struct TYPE_4__ {struct qm_fd fd; } ;
union qm_mr_entry {TYPE_2__ ern; } ;
struct sk_buff {int dummy; } ;
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;
struct net_device {int dummy; } ;
struct dpaa_priv {int /*<<< orphan*/  percpu_priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_dropped; } ;
struct dpaa_percpu_priv {TYPE_1__ stats; } ;
struct dpaa_fq {struct net_device* net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  count_ern (struct dpaa_percpu_priv*,union qm_mr_entry const*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* dpaa_cleanup_tx_fd (struct dpaa_priv const*,struct qm_fd const*) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 struct dpaa_percpu_priv* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void egress_ern(struct qman_portal *portal,
		       struct qman_fq *fq,
		       const union qm_mr_entry *msg)
{
	const struct qm_fd *fd = &msg->ern.fd;
	struct dpaa_percpu_priv *percpu_priv;
	const struct dpaa_priv *priv;
	struct net_device *net_dev;
	struct sk_buff *skb;

	net_dev = ((struct dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);
	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	percpu_priv->stats.tx_dropped++;
	percpu_priv->stats.tx_fifo_errors++;
	count_ern(percpu_priv, msg);

	skb = dpaa_cleanup_tx_fd(priv, fd);
	dev_kfree_skb_any(skb);
}