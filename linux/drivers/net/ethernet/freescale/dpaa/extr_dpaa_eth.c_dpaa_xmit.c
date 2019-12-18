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
struct rtnl_link_stats64 {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_fifo_errors; } ;
struct qman_fq {int dummy; } ;
struct qm_fd {scalar_t__ bpid; int /*<<< orphan*/  cmd; } ;
struct dpaa_priv {int /*<<< orphan*/  net_dev; int /*<<< orphan*/ * conf_fqs; struct qman_fq** egress_fqs; } ;

/* Variables and functions */
 int DPAA_ENQUEUE_RETRIES ; 
 int EBUSY ; 
 scalar_t__ FSL_DPAA_BPID_INV ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 scalar_t__ qm_fd_get_length (struct qm_fd*) ; 
 int qman_enqueue (struct qman_fq*,struct qm_fd*) ; 
 int /*<<< orphan*/  qman_fq_fqid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_dpaa_tx_fd (int /*<<< orphan*/ ,struct qman_fq*,struct qm_fd*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int dpaa_xmit(struct dpaa_priv *priv,
			    struct rtnl_link_stats64 *percpu_stats,
			    int queue,
			    struct qm_fd *fd)
{
	struct qman_fq *egress_fq;
	int err, i;

	egress_fq = priv->egress_fqs[queue];
	if (fd->bpid == FSL_DPAA_BPID_INV)
		fd->cmd |= cpu_to_be32(qman_fq_fqid(priv->conf_fqs[queue]));

	/* Trace this Tx fd */
	trace_dpaa_tx_fd(priv->net_dev, egress_fq, fd);

	for (i = 0; i < DPAA_ENQUEUE_RETRIES; i++) {
		err = qman_enqueue(egress_fq, fd);
		if (err != -EBUSY)
			break;
	}

	if (unlikely(err < 0)) {
		percpu_stats->tx_fifo_errors++;
		return err;
	}

	percpu_stats->tx_packets++;
	percpu_stats->tx_bytes += qm_fd_get_length(fd);

	return 0;
}