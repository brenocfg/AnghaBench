#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_11__ {scalar_t__ s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct nes_vnic {scalar_t__ local_ipaddr; struct nes_device* nesdev; } ;
struct TYPE_15__ {int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int /*<<< orphan*/  qp_id; } ;
struct nes_qp {int active_conn; TYPE_7__ ibqp; struct nes_cm_node* cm_node; void* private_data_len; struct iw_cm_id* cm_id; TYPE_2__ hwqp; } ;
struct nes_device {TYPE_5__* pcidev; } ;
struct nes_cm_node {scalar_t__ send_rdma0_op; int ord_size; int apbvt_set; struct nes_qp* nesqp; int /*<<< orphan*/  tos; } ;
struct nes_cm_info {void* loc_port; int /*<<< orphan*/  conn_type; struct iw_cm_id* cm_id; void* rem_port; void* rem_addr; void* loc_addr; } ;
struct TYPE_9__ {scalar_t__ ss_family; } ;
struct iw_cm_id {int /*<<< orphan*/  tos; int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;struct nes_qp* provider_data; int /*<<< orphan*/  device; TYPE_1__ remote_addr; int /*<<< orphan*/  m_remote_addr; int /*<<< orphan*/  m_local_addr; } ;
struct iw_cm_conn_param {scalar_t__ ord; scalar_t__ ird; scalar_t__ private_data; void* private_data_len; int /*<<< orphan*/  qpn; } ;
struct ib_qp {int dummy; } ;
struct TYPE_14__ {TYPE_4__* api; } ;
struct TYPE_13__ {int /*<<< orphan*/  devfn; } ;
struct TYPE_12__ {struct nes_cm_node* (* connect ) (TYPE_6__*,struct nes_vnic*,void*,void*,struct nes_cm_info*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int /*<<< orphan*/  NES_CM_IWARP_CONN_TYPE ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  NES_DBG_NLMSG ; 
 int /*<<< orphan*/  NES_MANAGE_APBVT_ADD ; 
 int /*<<< orphan*/  NES_MANAGE_APBVT_DEL ; 
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 
 scalar_t__ SEND_RDMA_READ_ZERO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_connects ; 
 TYPE_6__* g_cm_core ; 
 int /*<<< orphan*/  nes_add_ref (TYPE_7__*) ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,void*,...) ; 
 struct ib_qp* nes_get_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_manage_apbvt (struct nes_vnic*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (scalar_t__) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_ird_ord (struct nes_cm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 struct nes_cm_node* stub2 (TYPE_6__*,struct nes_vnic*,void*,void*,struct nes_cm_info*) ; 
 int /*<<< orphan*/  stub3 (struct iw_cm_id*) ; 
 struct nes_qp* to_nesqp (struct ib_qp*) ; 
 struct nes_vnic* to_nesvnic (int /*<<< orphan*/ ) ; 

int nes_connect(struct iw_cm_id *cm_id, struct iw_cm_conn_param *conn_param)
{
	struct ib_qp *ibqp;
	struct nes_qp *nesqp;
	struct nes_vnic *nesvnic;
	struct nes_device *nesdev;
	struct nes_cm_node *cm_node;
	struct nes_cm_info cm_info;
	int apbvt_set = 0;
	struct sockaddr_in *laddr = (struct sockaddr_in *)&cm_id->m_local_addr;
	struct sockaddr_in *raddr = (struct sockaddr_in *)&cm_id->m_remote_addr;

	if (cm_id->remote_addr.ss_family != AF_INET)
		return -ENOSYS;
	ibqp = nes_get_qp(cm_id->device, conn_param->qpn);
	if (!ibqp)
		return -EINVAL;
	nesqp = to_nesqp(ibqp);
	if (!nesqp)
		return -EINVAL;
	nesvnic = to_nesvnic(nesqp->ibqp.device);
	if (!nesvnic)
		return -EINVAL;
	nesdev = nesvnic->nesdev;
	if (!nesdev)
		return -EINVAL;

	if (!laddr->sin_port || !raddr->sin_port)
		return -EINVAL;

	nes_debug(NES_DBG_CM, "QP%u, current IP = 0x%08X, Destination IP = "
		  "0x%08X:0x%04X, local = 0x%08X:0x%04X.\n", nesqp->hwqp.qp_id,
		  ntohl(nesvnic->local_ipaddr), ntohl(raddr->sin_addr.s_addr),
		  ntohs(raddr->sin_port), ntohl(laddr->sin_addr.s_addr),
		  ntohs(laddr->sin_port));

	atomic_inc(&cm_connects);
	nesqp->active_conn = 1;

	/* cache the cm_id in the qp */
	nesqp->cm_id = cm_id;
	cm_id->provider_data = nesqp;
	nesqp->private_data_len = conn_param->private_data_len;

	nes_debug(NES_DBG_CM, "requested ord = 0x%08X.\n", (u32)conn_param->ord);
	nes_debug(NES_DBG_CM, "mpa private data len =%u\n",
		  conn_param->private_data_len);

	/* set up the connection params for the node */
	cm_info.loc_addr = ntohl(laddr->sin_addr.s_addr);
	cm_info.loc_port = ntohs(laddr->sin_port);
	cm_info.rem_addr = ntohl(raddr->sin_addr.s_addr);
	cm_info.rem_port = ntohs(raddr->sin_port);
	cm_info.cm_id = cm_id;
	cm_info.conn_type = NES_CM_IWARP_CONN_TYPE;

	if (laddr->sin_addr.s_addr != raddr->sin_addr.s_addr) {
		nes_manage_apbvt(nesvnic, cm_info.loc_port,
				 PCI_FUNC(nesdev->pcidev->devfn),
				 NES_MANAGE_APBVT_ADD);
		apbvt_set = 1;
	}

	cm_id->add_ref(cm_id);

	/* create a connect CM node connection */
	cm_node = g_cm_core->api->connect(g_cm_core, nesvnic,
					  conn_param->private_data_len, (void *)conn_param->private_data,
					  &cm_info);
	if (!cm_node) {
		if (apbvt_set)
			nes_manage_apbvt(nesvnic, cm_info.loc_port,
					 PCI_FUNC(nesdev->pcidev->devfn),
					 NES_MANAGE_APBVT_DEL);

		nes_debug(NES_DBG_NLMSG, "Delete loc_port = %04X\n",
			  cm_info.loc_port);
		cm_id->rem_ref(cm_id);
		return -ENOMEM;
	}

	record_ird_ord(cm_node, (u16)conn_param->ird, (u16)conn_param->ord);
	if (cm_node->send_rdma0_op == SEND_RDMA_READ_ZERO &&
				cm_node->ord_size == 0)
		cm_node->ord_size = 1;

	cm_node->apbvt_set = apbvt_set;
	cm_node->tos = cm_id->tos;
	nesqp->cm_node = cm_node;
	cm_node->nesqp = nesqp;
	nes_add_ref(&nesqp->ibqp);

	return 0;
}