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
struct qed_spq {int /*<<< orphan*/  cid; } ;
struct qed_hwfn {TYPE_1__* p_spq; } ;
struct qed_chain {int dummy; } ;
struct core_db_data {int /*<<< orphan*/  agg_flags; int /*<<< orphan*/  params; void* spq_prod; } ;
typedef  int /*<<< orphan*/  db ;
struct TYPE_3__ {struct qed_chain chain; } ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_DB_DATA_AGG_CMD ; 
 int /*<<< orphan*/  CORE_DB_DATA_AGG_VAL_SEL ; 
 int /*<<< orphan*/  CORE_DB_DATA_DEST ; 
 int /*<<< orphan*/  DB_AGG_CMD_SET ; 
 int /*<<< orphan*/  DB_DEST_XCM ; 
 int /*<<< orphan*/  DOORBELL (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DQ_DEMS_LEGACY ; 
 int /*<<< orphan*/  DQ_XCM_CORE_DQ_CF_CMD ; 
 int /*<<< orphan*/  DQ_XCM_CORE_SPQ_PROD_CMD ; 
 int EINVAL ; 
 int /*<<< orphan*/  QED_MSG_SPQ ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct core_db_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_chain_get_prod_idx (struct qed_chain*) ; 
 struct slow_path_element* qed_chain_produce (struct qed_chain*) ; 
 int /*<<< orphan*/  qed_db_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int qed_spq_hw_post(struct qed_hwfn *p_hwfn,
			   struct qed_spq *p_spq, struct qed_spq_entry *p_ent)
{
	struct qed_chain *p_chain = &p_hwfn->p_spq->chain;
	u16 echo = qed_chain_get_prod_idx(p_chain);
	struct slow_path_element	*elem;
	struct core_db_data		db;

	p_ent->elem.hdr.echo	= cpu_to_le16(echo);
	elem = qed_chain_produce(p_chain);
	if (!elem) {
		DP_NOTICE(p_hwfn, "Failed to produce from SPQ chain\n");
		return -EINVAL;
	}

	*elem = p_ent->elem; /* struct assignment */

	/* send a doorbell on the slow hwfn session */
	memset(&db, 0, sizeof(db));
	SET_FIELD(db.params, CORE_DB_DATA_DEST, DB_DEST_XCM);
	SET_FIELD(db.params, CORE_DB_DATA_AGG_CMD, DB_AGG_CMD_SET);
	SET_FIELD(db.params, CORE_DB_DATA_AGG_VAL_SEL,
		  DQ_XCM_CORE_SPQ_PROD_CMD);
	db.agg_flags = DQ_XCM_CORE_DQ_CF_CMD;
	db.spq_prod = cpu_to_le16(qed_chain_get_prod_idx(p_chain));

	/* make sure the SPQE is updated before the doorbell */
	wmb();

	DOORBELL(p_hwfn, qed_db_addr(p_spq->cid, DQ_DEMS_LEGACY), *(u32 *)&db);

	/* make sure doorbell is rang */
	wmb();

	DP_VERBOSE(p_hwfn, QED_MSG_SPQ,
		   "Doorbelled [0x%08x, CID 0x%08x] with Flags: %02x agg_params: %02x, prod: %04x\n",
		   qed_db_addr(p_spq->cid, DQ_DEMS_LEGACY),
		   p_spq->cid, db.params, db.agg_flags,
		   qed_chain_get_prod_idx(p_chain));

	return 0;
}