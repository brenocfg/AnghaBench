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
typedef  size_t u32 ;
struct kwqe {int dummy; } ;
struct kcqe {int dummy; } ;
struct iscsi_kwqe_conn_destroy {size_t reserved0; int /*<<< orphan*/  context_id; } ;
struct iscsi_kcqe {size_t iscsi_conn_id; int /*<<< orphan*/  iscsi_conn_context_id; int /*<<< orphan*/  completion_status; int /*<<< orphan*/  op_code; } ;
struct cnic_local {int /*<<< orphan*/  iscsi_conn; int /*<<< orphan*/  delete_task; struct cnic_context* ctx_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct cnic_context {unsigned long timestamp; int /*<<< orphan*/  ctx_flags; } ;
typedef  int /*<<< orphan*/  kcqe ;

/* Variables and functions */
 int /*<<< orphan*/  CNIC_ULP_ISCSI ; 
 int /*<<< orphan*/  CTX_FL_DELETE_WAIT ; 
 int /*<<< orphan*/  CTX_FL_OFFLD_START ; 
 int HZ ; 
 int /*<<< orphan*/  ISCSI_KCQE_COMPLETION_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ISCSI_KCQE_OPCODE_DESTROY_CONN ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cnic_bnx2x_destroy_ramrod (struct cnic_dev*,size_t) ; 
 int /*<<< orphan*/  cnic_free_bnx2x_conn_resc (struct cnic_dev*,size_t) ; 
 int /*<<< orphan*/  cnic_reply_bnx2x_kcqes (struct cnic_dev*,int /*<<< orphan*/ ,struct kcqe**,int) ; 
 int /*<<< orphan*/  cnic_wq ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memset (struct iscsi_kcqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int cnic_bnx2x_iscsi_destroy(struct cnic_dev *dev, struct kwqe *kwqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct iscsi_kwqe_conn_destroy *req =
		(struct iscsi_kwqe_conn_destroy *) kwqe;
	u32 l5_cid = req->reserved0;
	struct cnic_context *ctx = &cp->ctx_tbl[l5_cid];
	int ret = 0;
	struct iscsi_kcqe kcqe;
	struct kcqe *cqes[1];

	if (!test_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags))
		goto skip_cfc_delete;

	if (!time_after(jiffies, ctx->timestamp + (2 * HZ))) {
		unsigned long delta = ctx->timestamp + (2 * HZ) - jiffies;

		if (delta > (2 * HZ))
			delta = 0;

		set_bit(CTX_FL_DELETE_WAIT, &ctx->ctx_flags);
		queue_delayed_work(cnic_wq, &cp->delete_task, delta);
		goto destroy_reply;
	}

	ret = cnic_bnx2x_destroy_ramrod(dev, l5_cid);

skip_cfc_delete:
	cnic_free_bnx2x_conn_resc(dev, l5_cid);

	if (!ret) {
		atomic_dec(&cp->iscsi_conn);
		clear_bit(CTX_FL_OFFLD_START, &ctx->ctx_flags);
	}

destroy_reply:
	memset(&kcqe, 0, sizeof(kcqe));
	kcqe.op_code = ISCSI_KCQE_OPCODE_DESTROY_CONN;
	kcqe.iscsi_conn_id = l5_cid;
	kcqe.completion_status = ISCSI_KCQE_COMPLETION_STATUS_SUCCESS;
	kcqe.iscsi_conn_context_id = req->context_id;

	cqes[0] = (struct kcqe *) &kcqe;
	cnic_reply_bnx2x_kcqes(dev, CNIC_ULP_ISCSI, cqes, 1);

	return 0;
}