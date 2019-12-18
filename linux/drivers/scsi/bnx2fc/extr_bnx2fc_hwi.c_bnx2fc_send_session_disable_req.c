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
typedef  int u32 ;
struct kwqe {int dummy; } ;
struct fcoe_port {struct bnx2fc_interface* priv; } ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  op_code; } ;
struct fcoe_kwqe_conn_enable_disable {int* s_id; int* d_id; int vlan_tag; int /*<<< orphan*/  vlan_flag; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  context_id; int /*<<< orphan*/ * dst_mac_addr_hi; int /*<<< orphan*/ * dst_mac_addr_mid; int /*<<< orphan*/ * dst_mac_addr_lo; int /*<<< orphan*/ * src_mac_addr_hi; int /*<<< orphan*/ * src_mac_addr_mid; int /*<<< orphan*/ * src_mac_addr_lo; TYPE_1__ hdr; } ;
struct fcoe_ctlr {int /*<<< orphan*/ * dest_addr; } ;
struct fc_rport {int port_id; } ;
struct bnx2fc_rport {int sid; int /*<<< orphan*/  fcoe_conn_id; int /*<<< orphan*/  context_id; int /*<<< orphan*/ * src_addr; struct fc_rport* rport; } ;
struct bnx2fc_interface {int vlan_id; int /*<<< orphan*/  vlan_enabled; struct bnx2fc_hba* hba; } ;
struct bnx2fc_hba {TYPE_2__* cnic; } ;
struct TYPE_4__ {int (* submit_kwqes ) (TYPE_2__*,struct kwqe**,int) ;} ;

/* Variables and functions */
 int FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY_SHIFT ; 
 int FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID_SHIFT ; 
 int FCOE_KWQE_HEADER_LAYER_CODE_SHIFT ; 
 int FCOE_KWQE_LAYER_CODE ; 
 int /*<<< orphan*/  FCOE_KWQE_OPCODE_DISABLE_CONN ; 
 struct fcoe_ctlr* bnx2fc_to_ctlr (struct bnx2fc_interface*) ; 
 int /*<<< orphan*/  memset (struct fcoe_kwqe_conn_enable_disable*,int,int) ; 
 int stub1 (TYPE_2__*,struct kwqe**,int) ; 

int bnx2fc_send_session_disable_req(struct fcoe_port *port,
				    struct bnx2fc_rport *tgt)
{
	struct bnx2fc_interface *interface = port->priv;
	struct fcoe_ctlr *ctlr = bnx2fc_to_ctlr(interface);
	struct bnx2fc_hba *hba = interface->hba;
	struct fcoe_kwqe_conn_enable_disable disable_req;
	struct kwqe *kwqe_arr[2];
	struct fc_rport *rport = tgt->rport;
	int num_kwqes = 1;
	int rc = 0;
	u32 port_id;

	memset(&disable_req, 0x00,
	       sizeof(struct fcoe_kwqe_conn_enable_disable));
	disable_req.hdr.op_code = FCOE_KWQE_OPCODE_DISABLE_CONN;
	disable_req.hdr.flags =
		(FCOE_KWQE_LAYER_CODE << FCOE_KWQE_HEADER_LAYER_CODE_SHIFT);

	disable_req.src_mac_addr_lo[0] =  tgt->src_addr[5];
	disable_req.src_mac_addr_lo[1] =  tgt->src_addr[4];
	disable_req.src_mac_addr_mid[0] =  tgt->src_addr[3];
	disable_req.src_mac_addr_mid[1] =  tgt->src_addr[2];
	disable_req.src_mac_addr_hi[0] =  tgt->src_addr[1];
	disable_req.src_mac_addr_hi[1] =  tgt->src_addr[0];

	disable_req.dst_mac_addr_lo[0] =  ctlr->dest_addr[5];
	disable_req.dst_mac_addr_lo[1] =  ctlr->dest_addr[4];
	disable_req.dst_mac_addr_mid[0] = ctlr->dest_addr[3];
	disable_req.dst_mac_addr_mid[1] = ctlr->dest_addr[2];
	disable_req.dst_mac_addr_hi[0] = ctlr->dest_addr[1];
	disable_req.dst_mac_addr_hi[1] = ctlr->dest_addr[0];

	port_id = tgt->sid;
	disable_req.s_id[0] = (port_id & 0x000000FF);
	disable_req.s_id[1] = (port_id & 0x0000FF00) >> 8;
	disable_req.s_id[2] = (port_id & 0x00FF0000) >> 16;


	port_id = rport->port_id;
	disable_req.d_id[0] = (port_id & 0x000000FF);
	disable_req.d_id[1] = (port_id & 0x0000FF00) >> 8;
	disable_req.d_id[2] = (port_id & 0x00FF0000) >> 16;
	disable_req.context_id = tgt->context_id;
	disable_req.conn_id = tgt->fcoe_conn_id;
	disable_req.vlan_tag = interface->vlan_id <<
				FCOE_KWQE_CONN_ENABLE_DISABLE_VLAN_ID_SHIFT;
	disable_req.vlan_tag |=
			3 << FCOE_KWQE_CONN_ENABLE_DISABLE_PRIORITY_SHIFT;
	disable_req.vlan_flag = interface->vlan_enabled;

	kwqe_arr[0] = (struct kwqe *) &disable_req;

	if (hba->cnic && hba->cnic->submit_kwqes)
		rc = hba->cnic->submit_kwqes(hba->cnic, kwqe_arr, num_kwqes);

	return rc;
}