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
typedef  int u16 ;
struct qedi_ctx {int bdq_prod_idx; int rq_num_entries; TYPE_1__* bdq; int /*<<< orphan*/  dbg_ctx; } ;
struct iscsi_cqe_unsolicited {int rqe_opaque; int unsol_cqe_type; } ;
struct TYPE_2__ {scalar_t__ buf_addr; } ;

/* Variables and functions */
#define  ISCSI_CQE_UNSOLICITED_FIRST 131 
#define  ISCSI_CQE_UNSOLICITED_LAST 130 
#define  ISCSI_CQE_UNSOLICITED_MIDDLE 129 
#define  ISCSI_CQE_UNSOLICITED_SINGLE 128 
 int QEDI_BDQ_NUM ; 
 int /*<<< orphan*/  QEDI_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  QEDI_LOG_CONN ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 

__attribute__((used)) static void qedi_get_rq_bdq_buf(struct qedi_ctx *qedi,
				struct iscsi_cqe_unsolicited *cqe,
				char *ptr, int len)
{
	u16 idx = 0;

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "pld_len [%d], bdq_prod_idx [%d], idx [%d]\n",
		  len, qedi->bdq_prod_idx,
		  (qedi->bdq_prod_idx % qedi->rq_num_entries));

	/* Obtain buffer address from rqe_opaque */
	idx = cqe->rqe_opaque;
	if (idx > (QEDI_BDQ_NUM - 1)) {
		QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
			  "wrong idx %d returned by FW, dropping the unsolicited pkt\n",
			  idx);
		return;
	}

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "rqe_opaque [0x%p], idx [%d]\n", cqe->rqe_opaque, idx);

	QEDI_INFO(&qedi->dbg_ctx, QEDI_LOG_CONN,
		  "unsol_cqe_type = %d\n", cqe->unsol_cqe_type);
	switch (cqe->unsol_cqe_type) {
	case ISCSI_CQE_UNSOLICITED_SINGLE:
	case ISCSI_CQE_UNSOLICITED_FIRST:
		if (len)
			memcpy(ptr, (void *)qedi->bdq[idx].buf_addr, len);
		break;
	case ISCSI_CQE_UNSOLICITED_MIDDLE:
	case ISCSI_CQE_UNSOLICITED_LAST:
		break;
	default:
		break;
	}
}