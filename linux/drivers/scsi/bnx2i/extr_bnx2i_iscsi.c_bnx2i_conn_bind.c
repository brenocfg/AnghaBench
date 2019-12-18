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
typedef  int /*<<< orphan*/  uint64_t ;
struct iscsi_endpoint {struct bnx2i_endpoint* dd_data; } ;
struct iscsi_conn {struct bnx2i_conn* dd_data; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct bnx2i_hba {int /*<<< orphan*/  cnic_dev_type; TYPE_1__* netdev; } ;
struct bnx2i_endpoint {scalar_t__ state; struct bnx2i_hba* hba; int /*<<< orphan*/  ep_iscsi_cid; int /*<<< orphan*/  ep_cid; struct bnx2i_conn* conn; } ;
struct bnx2i_conn {struct bnx2i_endpoint* ep; int /*<<< orphan*/  fw_cid; int /*<<< orphan*/  iscsi_conn_cid; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2I_NX2_DEV_57710 ; 
 int /*<<< orphan*/  CNIC_ARM_CQE ; 
 int EEXIST ; 
 int EINVAL ; 
 int EIO ; 
 scalar_t__ EP_STATE_TCP_FIN_RCVD ; 
 scalar_t__ EP_STATE_TCP_RST_RCVD ; 
 int /*<<< orphan*/  KERN_ALERT ; 
 scalar_t__ bnx2i_adapter_ready (struct bnx2i_hba*) ; 
 int /*<<< orphan*/  bnx2i_arm_cq_event_coalescing (struct bnx2i_endpoint*,int /*<<< orphan*/ ) ; 
 int bnx2i_bind_conn_to_iscsi_cid (struct bnx2i_hba*,struct bnx2i_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2i_put_rq_buf (struct bnx2i_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ iscsi_conn_bind (struct iscsi_cls_session*,struct iscsi_cls_conn*,int) ; 
 int /*<<< orphan*/  iscsi_conn_printk (int /*<<< orphan*/ ,struct iscsi_conn*,char*,struct bnx2i_endpoint*,...) ; 
 struct bnx2i_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_conn_bind(struct iscsi_cls_session *cls_session,
			   struct iscsi_cls_conn *cls_conn,
			   uint64_t transport_fd, int is_leading)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct bnx2i_conn *bnx2i_conn = conn->dd_data;
	struct Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	struct bnx2i_hba *hba = iscsi_host_priv(shost);
	struct bnx2i_endpoint *bnx2i_ep;
	struct iscsi_endpoint *ep;
	int ret_code;

	ep = iscsi_lookup_endpoint(transport_fd);
	if (!ep)
		return -EINVAL;
	/*
	 * Forcefully terminate all in progress connection recovery at the
	 * earliest, either in bind(), send_pdu(LOGIN), or conn_start()
	 */
	if (bnx2i_adapter_ready(hba))
		return -EIO;

	bnx2i_ep = ep->dd_data;
	if ((bnx2i_ep->state == EP_STATE_TCP_FIN_RCVD) ||
	    (bnx2i_ep->state == EP_STATE_TCP_RST_RCVD))
		/* Peer disconnect via' FIN or RST */
		return -EINVAL;

	if (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		return -EINVAL;

	if (bnx2i_ep->hba != hba) {
		/* Error - TCP connection does not belong to this device
		 */
		iscsi_conn_printk(KERN_ALERT, cls_conn->dd_data,
				  "conn bind, ep=0x%p (%s) does not",
				  bnx2i_ep, bnx2i_ep->hba->netdev->name);
		iscsi_conn_printk(KERN_ALERT, cls_conn->dd_data,
				  "belong to hba (%s)\n",
				  hba->netdev->name);
		return -EEXIST;
	}
	bnx2i_ep->conn = bnx2i_conn;
	bnx2i_conn->ep = bnx2i_ep;
	bnx2i_conn->iscsi_conn_cid = bnx2i_ep->ep_iscsi_cid;
	bnx2i_conn->fw_cid = bnx2i_ep->ep_cid;

	ret_code = bnx2i_bind_conn_to_iscsi_cid(hba, bnx2i_conn,
						bnx2i_ep->ep_iscsi_cid);

	/* 5706/5708/5709 FW takes RQ as full when initiated, but for 57710
	 * driver needs to explicitly replenish RQ index during setup.
	 */
	if (test_bit(BNX2I_NX2_DEV_57710, &bnx2i_ep->hba->cnic_dev_type))
		bnx2i_put_rq_buf(bnx2i_conn, 0);

	bnx2i_arm_cq_event_coalescing(bnx2i_conn->ep, CNIC_ARM_CQE);
	return ret_code;
}