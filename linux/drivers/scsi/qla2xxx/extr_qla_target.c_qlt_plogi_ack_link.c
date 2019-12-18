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
struct scsi_qla_host {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * port_id; int /*<<< orphan*/  port_name; } ;
struct TYPE_4__ {TYPE_1__ isp24; } ;
struct imm_ntfy_from_isp {TYPE_2__ u; } ;
struct qlt_plogi_ack_t {struct fc_port* fcport; int /*<<< orphan*/  ref_count; struct imm_ntfy_from_isp iocb; } ;
struct fc_port {int disc_state; struct qlt_plogi_ack_t** plogi_link; int /*<<< orphan*/  port_name; } ;
typedef  enum qlt_plogi_link_t { ____Placeholder_qlt_plogi_link_t } qlt_plogi_link_t ;

/* Variables and functions */
#define  DSC_DELETED 129 
#define  DSC_DELETE_PEND 128 
 int QLT_PLOGI_LINK_CONFLICT ; 
 int QLT_PLOGI_LINK_SAME_WWN ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct fc_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qlt_plogi_ack_t*,int) ; 
 int /*<<< orphan*/  ql_dbg_tgt_mgt ; 
 int /*<<< orphan*/  qlt_plogi_ack_unref (struct scsi_qla_host*,struct qlt_plogi_ack_t*) ; 

void
qlt_plogi_ack_link(struct scsi_qla_host *vha, struct qlt_plogi_ack_t *pla,
    struct fc_port *sess, enum qlt_plogi_link_t link)
{
	struct imm_ntfy_from_isp *iocb = &pla->iocb;
	/* Inc ref_count first because link might already be pointing at pla */
	pla->ref_count++;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf097,
		"Linking sess %p [%d] wwn %8phC with PLOGI ACK to wwn %8phC"
		" s_id %02x:%02x:%02x, ref=%d pla %p link %d\n",
		sess, link, sess->port_name,
		iocb->u.isp24.port_name, iocb->u.isp24.port_id[2],
		iocb->u.isp24.port_id[1], iocb->u.isp24.port_id[0],
		pla->ref_count, pla, link);

	if (link == QLT_PLOGI_LINK_CONFLICT) {
		switch (sess->disc_state) {
		case DSC_DELETED:
		case DSC_DELETE_PEND:
			pla->ref_count--;
			return;
		default:
			break;
		}
	}

	if (sess->plogi_link[link])
		qlt_plogi_ack_unref(vha, sess->plogi_link[link]);

	if (link == QLT_PLOGI_LINK_SAME_WWN)
		pla->fcport = sess;

	sess->plogi_link[link] = pla;
}