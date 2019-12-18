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
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ data; } ;
struct qedf_ctx {scalar_t__ vlan_id; int /*<<< orphan*/  fipvlan_compl; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/  link_state; } ;
struct fip_vlan_desc {int /*<<< orphan*/  fd_vlan; } ;
struct fip_header {int /*<<< orphan*/  fip_dl_len; } ;
struct fip_desc {size_t fip_dlen; int fip_dtype; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int ETH_ALEN ; 
 size_t FIP_BPW ; 
#define  FIP_DT_VLAN 128 
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ QEDF_LINK_DOWN ; 
 int /*<<< orphan*/  QEDF_LOG_DISC ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  completion_done (int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_set_vlan_id (struct qedf_ctx*,scalar_t__) ; 

__attribute__((used)) static void qedf_fcoe_process_vlan_resp(struct qedf_ctx *qedf,
	struct sk_buff *skb)
{
	struct fip_header *fiph;
	struct fip_desc *desc;
	u16 vid = 0;
	ssize_t rlen;
	size_t dlen;

	fiph = (struct fip_header *)(((void *)skb->data) + 2 * ETH_ALEN + 2);

	rlen = ntohs(fiph->fip_dl_len) * 4;
	desc = (struct fip_desc *)(fiph + 1);
	while (rlen > 0) {
		dlen = desc->fip_dlen * FIP_BPW;
		switch (desc->fip_dtype) {
		case FIP_DT_VLAN:
			vid = ntohs(((struct fip_vlan_desc *)desc)->fd_vlan);
			break;
		}
		desc = (struct fip_desc *)((char *)desc + dlen);
		rlen -= dlen;
	}

	if (atomic_read(&qedf->link_state) == QEDF_LINK_DOWN) {
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "Dropping VLAN response as link is down.\n");
		return;
	}

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "VLAN response, "
		   "vid=0x%x.\n", vid);

	if (vid > 0 && qedf->vlan_id != vid) {
		qedf_set_vlan_id(qedf, vid);

		/* Inform waiter that it's ok to call fcoe_ctlr_link up() */
		if (!completion_done(&qedf->fipvlan_compl))
			complete(&qedf->fipvlan_compl);
	}
}