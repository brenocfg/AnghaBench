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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {void* echo; } ;
struct slow_path_element {TYPE_2__ hdr; } ;
struct qed_spq_entry {struct slow_path_element elem; } ;
struct core_db_data {int /*<<< orphan*/  agg_flags; int /*<<< orphan*/  params; void* spq_prod; } ;
struct qed_spq {int /*<<< orphan*/  cid; int /*<<< orphan*/  db_addr_offset; struct core_db_data db_data; } ;
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct qed_chain {int dummy; } ;
struct TYPE_3__ {struct qed_chain chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOORBELL (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_chain_get_prod_idx (struct qed_chain*) ; 
 struct slow_path_element* qed_chain_produce (struct qed_chain*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int qed_spq_hw_post(struct qed_hwfn *p_hwfn,
			   struct qed_spq *p_spq, struct qed_spq_entry *p_ent)
{
	struct qed_chain *p_chain = &p_hwfn->p_spq->chain;
	struct core_db_data *p_db_data = &p_spq->db_data;
	u16 echo = qed_chain_get_prod_idx(p_chain);
	struct slow_path_element	*elem;

	p_ent->elem.hdr.echo	= cpu_to_le16(echo);
	elem = qed_chain_produce(p_chain);
	if (!elem) {
		DP_NOTICE(p_hwfn, "Failed to produce from SPQ chain\n");
		return -EINVAL;
	}

	*elem = p_ent->elem; /* struct assignment */

	/* send a doorbell on the slow hwfn session */
	p_db_data->spq_prod = cpu_to_le16(qed_chain_get_prod_idx(p_chain));

	/* make sure the SPQE is updated before the doorbell */
	wmb();

	DOORBELL(p_hwfn, p_spq->db_addr_offset, *(u32 *)p_db_data);

	/* make sure doorbell is rang */
	wmb();

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Doorbelled [0x%08x, CID 0x%08x] with Flags: %02x agg_params: %02x, prod: %04x\n",
		   p_spq->db_addr_offset,
		   p_spq->cid,
		   p_db_data->params,
		   p_db_data->agg_flags, qed_chain_get_prod_idx(p_chain));

	return 0;
}