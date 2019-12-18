#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct ntb_transport_qp {unsigned int qp_num; int client_ready; unsigned int tx_mw_size; unsigned int tx_max_frame; unsigned int tx_max_entry; int /*<<< orphan*/  rxc_db_work; int /*<<< orphan*/  tx_free_q; int /*<<< orphan*/  rx_free_q; int /*<<< orphan*/  rx_pend_q; int /*<<< orphan*/  rx_post_q; int /*<<< orphan*/  ntb_tx_free_q_lock; int /*<<< orphan*/  ntb_rx_q_lock; int /*<<< orphan*/  link_cleanup; int /*<<< orphan*/  link_work; int /*<<< orphan*/ * debugfs_stats; int /*<<< orphan*/ * debugfs_dir; scalar_t__ tx_mw; scalar_t__ rx_info; scalar_t__ tx_mw_phys; int /*<<< orphan*/ * event_handler; int /*<<< orphan*/  ndev; struct ntb_transport_ctx* transport; } ;
struct ntb_transport_ctx {unsigned int mw_count; unsigned int qp_count; scalar_t__ debugfs_node_dir; TYPE_1__* mw_vec; int /*<<< orphan*/  ndev; struct ntb_transport_qp* qp_vec; } ;
struct ntb_rx_info {int dummy; } ;
typedef  scalar_t__ resource_size_t ;
typedef  scalar_t__ phys_addr_t ;
struct TYPE_2__ {scalar_t__ phys_size; scalar_t__ vbase; scalar_t__ phys_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int QP_TO_MW (struct ntb_transport_ctx*,unsigned int) ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/ * debugfs_create_dir (char*,scalar_t__) ; 
 int /*<<< orphan*/ * debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ntb_transport_qp*,int /*<<< orphan*/ *) ; 
 scalar_t__ max_mw_size ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ntb_qp_debugfs_stats ; 
 int /*<<< orphan*/  ntb_qp_link_cleanup_work ; 
 int /*<<< orphan*/  ntb_qp_link_down_reset (struct ntb_transport_qp*) ; 
 int /*<<< orphan*/  ntb_qp_link_work ; 
 int /*<<< orphan*/  ntb_transport_rxc_db ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  transport_mtu ; 

__attribute__((used)) static int ntb_transport_init_queue(struct ntb_transport_ctx *nt,
				    unsigned int qp_num)
{
	struct ntb_transport_qp *qp;
	phys_addr_t mw_base;
	resource_size_t mw_size;
	unsigned int num_qps_mw, tx_size;
	unsigned int mw_num, mw_count, qp_count;
	u64 qp_offset;

	mw_count = nt->mw_count;
	qp_count = nt->qp_count;

	mw_num = QP_TO_MW(nt, qp_num);

	qp = &nt->qp_vec[qp_num];
	qp->qp_num = qp_num;
	qp->transport = nt;
	qp->ndev = nt->ndev;
	qp->client_ready = false;
	qp->event_handler = NULL;
	ntb_qp_link_down_reset(qp);

	if (mw_num < qp_count % mw_count)
		num_qps_mw = qp_count / mw_count + 1;
	else
		num_qps_mw = qp_count / mw_count;

	mw_base = nt->mw_vec[mw_num].phys_addr;
	mw_size = nt->mw_vec[mw_num].phys_size;

	if (max_mw_size && mw_size > max_mw_size)
		mw_size = max_mw_size;

	tx_size = (unsigned int)mw_size / num_qps_mw;
	qp_offset = tx_size * (qp_num / mw_count);

	qp->tx_mw_size = tx_size;
	qp->tx_mw = nt->mw_vec[mw_num].vbase + qp_offset;
	if (!qp->tx_mw)
		return -EINVAL;

	qp->tx_mw_phys = mw_base + qp_offset;
	if (!qp->tx_mw_phys)
		return -EINVAL;

	tx_size -= sizeof(struct ntb_rx_info);
	qp->rx_info = qp->tx_mw + tx_size;

	/* Due to housekeeping, there must be atleast 2 buffs */
	qp->tx_max_frame = min(transport_mtu, tx_size / 2);
	qp->tx_max_entry = tx_size / qp->tx_max_frame;

	if (nt->debugfs_node_dir) {
		char debugfs_name[4];

		snprintf(debugfs_name, 4, "qp%d", qp_num);
		qp->debugfs_dir = debugfs_create_dir(debugfs_name,
						     nt->debugfs_node_dir);

		qp->debugfs_stats = debugfs_create_file("stats", S_IRUSR,
							qp->debugfs_dir, qp,
							&ntb_qp_debugfs_stats);
	} else {
		qp->debugfs_dir = NULL;
		qp->debugfs_stats = NULL;
	}

	INIT_DELAYED_WORK(&qp->link_work, ntb_qp_link_work);
	INIT_WORK(&qp->link_cleanup, ntb_qp_link_cleanup_work);

	spin_lock_init(&qp->ntb_rx_q_lock);
	spin_lock_init(&qp->ntb_tx_free_q_lock);

	INIT_LIST_HEAD(&qp->rx_post_q);
	INIT_LIST_HEAD(&qp->rx_pend_q);
	INIT_LIST_HEAD(&qp->rx_free_q);
	INIT_LIST_HEAD(&qp->tx_free_q);

	tasklet_init(&qp->rxc_db_work, ntb_transport_rxc_db,
		     (unsigned long)qp);

	return 0;
}