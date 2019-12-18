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
struct dpni_queue_id {scalar_t__ fqid; int /*<<< orphan*/  member_0; } ;
struct dpni_queue {int dummy; } ;
struct dpaa2_eth_priv {int num_fqs; int /*<<< orphan*/  enqueue; int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mc_token; int /*<<< orphan*/  mc_io; struct dpaa2_eth_fq* fq; } ;
struct dpaa2_eth_fq {scalar_t__ type; scalar_t__* tx_fqid; int /*<<< orphan*/  flowid; } ;

/* Variables and functions */
 scalar_t__ DPAA2_TX_CONF_FQ ; 
 int /*<<< orphan*/  DPNI_ENQUEUE_FQID_VER_MAJOR ; 
 int /*<<< orphan*/  DPNI_ENQUEUE_FQID_VER_MINOR ; 
 int /*<<< orphan*/  DPNI_QUEUE_TX ; 
 scalar_t__ dpaa2_eth_cmp_dpni_ver (struct dpaa2_eth_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpaa2_eth_enqueue_fq ; 
 int /*<<< orphan*/  dpaa2_eth_enqueue_qd ; 
 int dpaa2_eth_tc_count (struct dpaa2_eth_priv*) ; 
 int dpni_get_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dpni_queue*,struct dpni_queue_id*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void update_tx_fqids(struct dpaa2_eth_priv *priv)
{
	struct dpni_queue_id qid = {0};
	struct dpaa2_eth_fq *fq;
	struct dpni_queue queue;
	int i, j, err;

	/* We only use Tx FQIDs for FQID-based enqueue, so check
	 * if DPNI version supports it before updating FQIDs
	 */
	if (dpaa2_eth_cmp_dpni_ver(priv, DPNI_ENQUEUE_FQID_VER_MAJOR,
				   DPNI_ENQUEUE_FQID_VER_MINOR) < 0)
		return;

	for (i = 0; i < priv->num_fqs; i++) {
		fq = &priv->fq[i];
		if (fq->type != DPAA2_TX_CONF_FQ)
			continue;
		for (j = 0; j < dpaa2_eth_tc_count(priv); j++) {
			err = dpni_get_queue(priv->mc_io, 0, priv->mc_token,
					     DPNI_QUEUE_TX, j, fq->flowid,
					     &queue, &qid);
			if (err)
				goto out_err;

			fq->tx_fqid[j] = qid.fqid;
			if (fq->tx_fqid[j] == 0)
				goto out_err;
		}
	}

	priv->enqueue = dpaa2_eth_enqueue_fq;

	return;

out_err:
	netdev_info(priv->net_dev,
		    "Error reading Tx FQID, fallback to QDID-based enqueue\n");
	priv->enqueue = dpaa2_eth_enqueue_qd;
}