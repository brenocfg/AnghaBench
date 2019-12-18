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
struct kcqe {int dummy; } ;
struct fcoe_kcqe {size_t fcoe_conn_id; } ;
struct cnic_local {struct cnic_context* ctx_tbl; } ;
struct cnic_dev {struct cnic_local* cnic_priv; } ;
struct cnic_context {int wait_cond; int /*<<< orphan*/  waitq; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
 size_t BNX2X_FCOE_L5_CID_BASE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cnic_process_fcoe_term_conn(struct cnic_dev *dev, struct kcqe *kcqe)
{
	struct cnic_local *cp = dev->cnic_priv;
	struct fcoe_kcqe *fc_kcqe = (struct fcoe_kcqe *) kcqe;
	u32 l5_cid = fc_kcqe->fcoe_conn_id + BNX2X_FCOE_L5_CID_BASE;
	struct cnic_context *ctx = &cp->ctx_tbl[l5_cid];

	ctx->timestamp = jiffies;
	ctx->wait_cond = 1;
	wake_up(&ctx->waitq);
}