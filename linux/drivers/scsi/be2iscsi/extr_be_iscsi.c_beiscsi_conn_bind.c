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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  u64 ;
struct iscsi_endpoint {struct beiscsi_endpoint* dd_data; } ;
struct iscsi_conn {struct beiscsi_conn* dd_data; } ;
struct iscsi_cls_session {int dummy; } ;
struct iscsi_cls_conn {struct iscsi_conn* dd_data; } ;
struct hwi_wrb_context {int /*<<< orphan*/  doorbell_offset; } ;
struct hwi_controller {struct hwi_wrb_context* wrb_context; } ;
struct beiscsi_hba {struct beiscsi_conn** conn_table; struct hwi_controller* phwi_ctrlr; } ;
struct beiscsi_endpoint {int /*<<< orphan*/  ep_cid; struct beiscsi_conn* conn; struct beiscsi_hba* phba; } ;
struct beiscsi_conn {int /*<<< orphan*/  doorbell_offset; struct beiscsi_endpoint* ep; int /*<<< orphan*/  beiscsi_conn_cid; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEISCSI_LOG_CONFIG ; 
 size_t BE_GET_CRI_FROM_CID (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,struct beiscsi_conn*,struct beiscsi_conn*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct beiscsi_hba*,...) ; 
 scalar_t__ iscsi_conn_bind (struct iscsi_cls_session*,struct iscsi_cls_conn*,int) ; 
 struct beiscsi_hba* iscsi_host_priv (struct Scsi_Host*) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* iscsi_session_to_shost (struct iscsi_cls_session*) ; 

int beiscsi_conn_bind(struct iscsi_cls_session *cls_session,
		      struct iscsi_cls_conn *cls_conn,
		      u64 transport_fd, int is_leading)
{
	struct iscsi_conn *conn = cls_conn->dd_data;
	struct beiscsi_conn *beiscsi_conn = conn->dd_data;
	struct Scsi_Host *shost = iscsi_session_to_shost(cls_session);
	struct beiscsi_hba *phba = iscsi_host_priv(shost);
	struct hwi_controller *phwi_ctrlr = phba->phwi_ctrlr;
	struct hwi_wrb_context *pwrb_context;
	struct beiscsi_endpoint *beiscsi_ep;
	struct iscsi_endpoint *ep;
	uint16_t cri_index;

	ep = iscsi_lookup_endpoint(transport_fd);
	if (!ep)
		return -EINVAL;

	beiscsi_ep = ep->dd_data;

	if (iscsi_conn_bind(cls_session, cls_conn, is_leading))
		return -EINVAL;

	if (beiscsi_ep->phba != phba) {
		beiscsi_log(phba, KERN_ERR, BEISCSI_LOG_CONFIG,
			    "BS_%d : beiscsi_ep->hba=%p not equal to phba=%p\n",
			    beiscsi_ep->phba, phba);

		return -EEXIST;
	}
	cri_index = BE_GET_CRI_FROM_CID(beiscsi_ep->ep_cid);
	if (phba->conn_table[cri_index]) {
		if (beiscsi_conn != phba->conn_table[cri_index] ||
		    beiscsi_ep != phba->conn_table[cri_index]->ep) {
			__beiscsi_log(phba, KERN_ERR,
				      "BS_%d : conn_table not empty at %u: cid %u conn %p:%p\n",
				      cri_index,
				      beiscsi_ep->ep_cid,
				      beiscsi_conn,
				      phba->conn_table[cri_index]);
			return -EINVAL;
		}
	}

	beiscsi_conn->beiscsi_conn_cid = beiscsi_ep->ep_cid;
	beiscsi_conn->ep = beiscsi_ep;
	beiscsi_ep->conn = beiscsi_conn;
	/**
	 * Each connection is associated with a WRBQ kept in wrb_context.
	 * Store doorbell offset for transmit path.
	 */
	pwrb_context = &phwi_ctrlr->wrb_context[cri_index];
	beiscsi_conn->doorbell_offset = pwrb_context->doorbell_offset;
	beiscsi_log(phba, KERN_INFO, BEISCSI_LOG_CONFIG,
		    "BS_%d : cid %d phba->conn_table[%u]=%p\n",
		    beiscsi_ep->ep_cid, cri_index, beiscsi_conn);
	phba->conn_table[cri_index] = beiscsi_conn;
	return 0;
}