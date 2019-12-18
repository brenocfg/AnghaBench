#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct kwqe {int dummy; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  op_code; } ;
struct iscsi_kwqe_conn_destroy {int context_id; scalar_t__ reserved0; TYPE_1__ hdr; } ;
struct bnx2i_hba {TYPE_3__* cnic; } ;
struct bnx2i_endpoint {int ep_cid; scalar_t__ ep_iscsi_cid; TYPE_2__* hba; } ;
struct TYPE_6__ {int (* submit_kwqes ) (TYPE_3__*,struct kwqe**,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  cnic_dev_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 int EINVAL ; 
 int ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT ; 
 int ISCSI_KWQE_LAYER_CODE ; 
 int /*<<< orphan*/  ISCSI_KWQE_OPCODE_DESTROY_CONN ; 
 int /*<<< orphan*/  memset (struct iscsi_kwqe_conn_destroy*,int,int) ; 
 int stub1 (TYPE_3__*,struct kwqe**,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int bnx2i_send_conn_destroy(struct bnx2i_hba *hba, struct bnx2i_endpoint *ep)
{
	struct kwqe *kwqe_arr[2];
	struct iscsi_kwqe_conn_destroy conn_cleanup;
	int rc = -EINVAL;

	memset(&conn_cleanup, 0x00, sizeof(struct iscsi_kwqe_conn_destroy));

	conn_cleanup.hdr.op_code = ISCSI_KWQE_OPCODE_DESTROY_CONN;
	conn_cleanup.hdr.flags =
		(ISCSI_KWQE_LAYER_CODE << ISCSI_KWQE_HEADER_LAYER_CODE_SHIFT);
	/* 5771x requires conn context id to be passed as is */
	if (test_bit(BNX2I_NX2_DEV_57710, &ep->hba->cnic_dev_type))
		conn_cleanup.context_id = ep->ep_cid;
	else
		conn_cleanup.context_id = (ep->ep_cid >> 7);

	conn_cleanup.reserved0 = (u16)ep->ep_iscsi_cid;

	kwqe_arr[0] = (struct kwqe *) &conn_cleanup;
	if (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, 1);

	return rc;
}