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
typedef  int /*<<< orphan*/  u16 ;
struct qede_dev {int /*<<< orphan*/  cdev; struct qed_eth_ops* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* stringify ) (TYPE_1__*,char*) ;} ;
struct qede_arfs_fltr_node {int used; int filter_op; scalar_t__ vfid; int /*<<< orphan*/  sw_id; TYPE_1__ tuple; int /*<<< orphan*/  b_is_drop; int /*<<< orphan*/  buf_len; int /*<<< orphan*/  mapping; } ;
struct qed_ntuple_filter_params {int b_is_add; int b_is_vf; scalar_t__ vf_id; int /*<<< orphan*/  b_is_drop; int /*<<< orphan*/  qid; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct qed_eth_ops {int /*<<< orphan*/  (* ntuple_filter_config ) (int /*<<< orphan*/ ,struct qede_arfs_fltr_node*,struct qed_ntuple_filter_params*) ;} ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qede_dev*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_RX_STATUS ; 
 int QEDE_FILTER_PRINT_MAX_LEN ; 
 int /*<<< orphan*/  memset (struct qed_ntuple_filter_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,struct qede_arfs_fltr_node*,struct qed_ntuple_filter_params*) ; 

__attribute__((used)) static void qede_configure_arfs_fltr(struct qede_dev *edev,
				     struct qede_arfs_fltr_node *n,
				     u16 rxq_id, bool add_fltr)
{
	const struct qed_eth_ops *op = edev->ops;
	struct qed_ntuple_filter_params params;

	if (n->used)
		return;

	memset(&params, 0, sizeof(params));

	params.addr = n->mapping;
	params.length = n->buf_len;
	params.qid = rxq_id;
	params.b_is_add = add_fltr;
	params.b_is_drop = n->b_is_drop;

	if (n->vfid) {
		params.b_is_vf = true;
		params.vf_id = n->vfid - 1;
	}

	if (n->tuple.stringify) {
		char tuple_buffer[QEDE_FILTER_PRINT_MAX_LEN];

		n->tuple.stringify(&n->tuple, tuple_buffer);
		DP_VERBOSE(edev, NETIF_MSG_RX_STATUS,
			   "%s sw_id[0x%llx]: %s [vf %u queue %d]\n",
			   add_fltr ? "Adding" : "Deleting",
			   n->sw_id, tuple_buffer, n->vfid, rxq_id);
	}

	n->used = true;
	n->filter_op = add_fltr;
	op->ntuple_filter_config(edev->cdev, n, &params);
}