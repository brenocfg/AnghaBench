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
struct ntb_transport_qp {unsigned int rx_max_frame; unsigned int rx_max_entry; unsigned int rx_alloc_entry; scalar_t__ tx_index; scalar_t__ tx_pkts; scalar_t__ rx_pkts; TYPE_1__* rx_buff; TYPE_1__* remote_rx_info; int /*<<< orphan*/  rx_free_q; int /*<<< orphan*/  ntb_rx_q_lock; scalar_t__ rx_index; } ;
struct ntb_transport_mw {TYPE_1__* virt_addr; scalar_t__ xlat_size; } ;
struct ntb_transport_ctx {unsigned int mw_count; unsigned int qp_count; struct ntb_transport_mw* mw_vec; struct ntb_dev* ndev; struct ntb_transport_qp* qp_vec; } ;
struct ntb_rx_info {int dummy; } ;
struct ntb_queue_entry {int /*<<< orphan*/  entry; struct ntb_transport_qp* qp; } ;
struct ntb_payload_header {int dummy; } ;
struct ntb_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int QP_TO_MW (struct ntb_transport_ctx*,unsigned int) ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 struct ntb_queue_entry* kzalloc_node (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ntb_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transport_mtu ; 

__attribute__((used)) static int ntb_transport_setup_qp_mw(struct ntb_transport_ctx *nt,
				     unsigned int qp_num)
{
	struct ntb_transport_qp *qp = &nt->qp_vec[qp_num];
	struct ntb_transport_mw *mw;
	struct ntb_dev *ndev = nt->ndev;
	struct ntb_queue_entry *entry;
	unsigned int rx_size, num_qps_mw;
	unsigned int mw_num, mw_count, qp_count;
	unsigned int i;
	int node;

	mw_count = nt->mw_count;
	qp_count = nt->qp_count;

	mw_num = QP_TO_MW(nt, qp_num);
	mw = &nt->mw_vec[mw_num];

	if (!mw->virt_addr)
		return -ENOMEM;

	if (mw_num < qp_count % mw_count)
		num_qps_mw = qp_count / mw_count + 1;
	else
		num_qps_mw = qp_count / mw_count;

	rx_size = (unsigned int)mw->xlat_size / num_qps_mw;
	qp->rx_buff = mw->virt_addr + rx_size * (qp_num / mw_count);
	rx_size -= sizeof(struct ntb_rx_info);

	qp->remote_rx_info = qp->rx_buff + rx_size;

	/* Due to housekeeping, there must be atleast 2 buffs */
	qp->rx_max_frame = min(transport_mtu, rx_size / 2);
	qp->rx_max_entry = rx_size / qp->rx_max_frame;
	qp->rx_index = 0;

	/*
	 * Checking to see if we have more entries than the default.
	 * We should add additional entries if that is the case so we
	 * can be in sync with the transport frames.
	 */
	node = dev_to_node(&ndev->dev);
	for (i = qp->rx_alloc_entry; i < qp->rx_max_entry; i++) {
		entry = kzalloc_node(sizeof(*entry), GFP_KERNEL, node);
		if (!entry)
			return -ENOMEM;

		entry->qp = qp;
		ntb_list_add(&qp->ntb_rx_q_lock, &entry->entry,
			     &qp->rx_free_q);
		qp->rx_alloc_entry++;
	}

	qp->remote_rx_info->entry = qp->rx_max_entry - 1;

	/* setup the hdr offsets with 0's */
	for (i = 0; i < qp->rx_max_entry; i++) {
		void *offset = (qp->rx_buff + qp->rx_max_frame * (i + 1) -
				sizeof(struct ntb_payload_header));
		memset(offset, 0, sizeof(struct ntb_payload_header));
	}

	qp->rx_pkts = 0;
	qp->tx_pkts = 0;
	qp->tx_index = 0;

	return 0;
}