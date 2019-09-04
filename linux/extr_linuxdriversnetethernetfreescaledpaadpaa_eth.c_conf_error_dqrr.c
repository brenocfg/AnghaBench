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
struct qman_portal {int dummy; } ;
struct qman_fq {int /*<<< orphan*/  fqid; } ;
struct qm_dqrr_entry {int /*<<< orphan*/  fd; } ;
struct net_device {int dummy; } ;
struct dpaa_priv {int /*<<< orphan*/  percpu_priv; } ;
struct dpaa_percpu_priv {int dummy; } ;
struct dpaa_fq {struct net_device* net_dev; } ;
typedef  enum qman_cb_dqrr_result { ____Placeholder_qman_cb_dqrr_result } qman_cb_dqrr_result ;

/* Variables and functions */
 scalar_t__ dpaa_eth_napi_schedule (struct dpaa_percpu_priv*,struct qman_portal*) ; 
 int /*<<< orphan*/  dpaa_tx_error (struct net_device*,struct dpaa_priv*,struct dpaa_percpu_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dpaa_priv* netdev_priv (struct net_device*) ; 
 int qman_cb_dqrr_consume ; 
 int qman_cb_dqrr_stop ; 
 struct dpaa_percpu_priv* this_cpu_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum qman_cb_dqrr_result conf_error_dqrr(struct qman_portal *portal,
						struct qman_fq *fq,
						const struct qm_dqrr_entry *dq)
{
	struct dpaa_percpu_priv *percpu_priv;
	struct net_device *net_dev;
	struct dpaa_priv *priv;

	net_dev = ((struct dpaa_fq *)fq)->net_dev;
	priv = netdev_priv(net_dev);

	percpu_priv = this_cpu_ptr(priv->percpu_priv);

	if (dpaa_eth_napi_schedule(percpu_priv, portal))
		return qman_cb_dqrr_stop;

	dpaa_tx_error(net_dev, priv, percpu_priv, &dq->fd, fq->fqid);

	return qman_cb_dqrr_consume;
}