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
struct qedi_conn {int /*<<< orphan*/  iscsi_conn_id; TYPE_2__* ep; TYPE_1__* qedi; } ;
struct iscsi_db_data {int params; int /*<<< orphan*/  sq_prod; scalar_t__ agg_flags; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_sq_prod_idx; int /*<<< orphan*/  sq_prod_idx; int /*<<< orphan*/  p_doorbell; } ;
struct TYPE_3__ {int /*<<< orphan*/  dbg_ctx; } ;

/* Variables and functions */
 int DB_AGG_CMD_SET ; 
 int DB_DEST_XCM ; 
 int DQ_XCM_ISCSI_SQ_PROD_CMD ; 
 int ISCSI_DB_DATA_AGG_CMD_SHIFT ; 
 int ISCSI_DB_DATA_AGG_VAL_SEL_SHIFT ; 
 int ISCSI_DB_DATA_DEST_SHIFT ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDI_LOG_MP_REQ ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qedi_ring_doorbell(struct qedi_conn *qedi_conn)
{
	struct iscsi_db_data dbell = { 0 };

	dbell.agg_flags = 0;

	dbell.params |= DB_DEST_XCM << ISCSI_DB_DATA_DEST_SHIFT;
	dbell.params |= DB_AGG_CMD_SET << ISCSI_DB_DATA_AGG_CMD_SHIFT;
	dbell.params |=
		   DQ_XCM_ISCSI_SQ_PROD_CMD << ISCSI_DB_DATA_AGG_VAL_SEL_SHIFT;

	dbell.sq_prod = qedi_conn->ep->fw_sq_prod_idx;
	writel(*(u32 *)&dbell, qedi_conn->ep->p_doorbell);

	/* Make sure fw write idx is coherent, and include both memory barriers
	 * as a failsafe as for some architectures the call is the same but on
	 * others they are two different assembly operations.
	 */
	wmb();
	QEDI_INFO(&qedi_conn->qedi->dbg_ctx, QEDI_LOG_MP_REQ,
		  "prod_idx=0x%x, fw_prod_idx=0x%x, cid=0x%x\n",
		  qedi_conn->ep->sq_prod_idx, qedi_conn->ep->fw_sq_prod_idx,
		  qedi_conn->iscsi_conn_id);
}