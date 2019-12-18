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
typedef  int /*<<< orphan*/  u32 ;
struct qed_ll2_rx_packet {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  rx_num_desc; int /*<<< orphan*/  conn_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcq_chain; struct qed_ll2_rx_packet* descq_array; int /*<<< orphan*/  rxq_chain; } ;
struct qed_ll2_info {TYPE_2__ input; TYPE_1__ rx_queue; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct core_rx_fast_path_cqe {int dummy; } ;
struct core_rx_bd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QED_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_NEXT_PTR ; 
 int /*<<< orphan*/  QED_CHAIN_MODE_PBL ; 
 int /*<<< orphan*/  QED_CHAIN_USE_TO_CONSUME_PRODUCE ; 
 int /*<<< orphan*/  QED_MSG_LL2 ; 
 struct qed_ll2_rx_packet* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int qed_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_chain_get_capacity (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_ll2_acquire_connection_rx(struct qed_hwfn *p_hwfn,
			      struct qed_ll2_info *p_ll2_info)
{
	struct qed_ll2_rx_packet *p_descq;
	u32 capacity;
	int rc = 0;

	if (!p_ll2_info->input.rx_num_desc)
		goto out;

	rc = qed_chain_alloc(p_hwfn->cdev,
			     QED_CHAIN_USE_TO_CONSUME_PRODUCE,
			     QED_CHAIN_MODE_NEXT_PTR,
			     QED_CHAIN_CNT_TYPE_U16,
			     p_ll2_info->input.rx_num_desc,
			     sizeof(struct core_rx_bd),
			     &p_ll2_info->rx_queue.rxq_chain, NULL);
	if (rc) {
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 rxq chain\n");
		goto out;
	}

	capacity = qed_chain_get_capacity(&p_ll2_info->rx_queue.rxq_chain);
	p_descq = kcalloc(capacity, sizeof(struct qed_ll2_rx_packet),
			  GFP_KERNEL);
	if (!p_descq) {
		rc = -ENOMEM;
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 Rx desc\n");
		goto out;
	}
	p_ll2_info->rx_queue.descq_array = p_descq;

	rc = qed_chain_alloc(p_hwfn->cdev,
			     QED_CHAIN_USE_TO_CONSUME_PRODUCE,
			     QED_CHAIN_MODE_PBL,
			     QED_CHAIN_CNT_TYPE_U16,
			     p_ll2_info->input.rx_num_desc,
			     sizeof(struct core_rx_fast_path_cqe),
			     &p_ll2_info->rx_queue.rcq_chain, NULL);
	if (rc) {
		DP_NOTICE(p_hwfn, "Failed to allocate ll2 rcq chain\n");
		goto out;
	}

	DP_VERBOSE(p_hwfn, QED_MSG_LL2,
		   "Allocated LL2 Rxq [Type %08x] with 0x%08x buffers\n",
		   p_ll2_info->input.conn_type, p_ll2_info->input.rx_num_desc);

out:
	return rc;
}