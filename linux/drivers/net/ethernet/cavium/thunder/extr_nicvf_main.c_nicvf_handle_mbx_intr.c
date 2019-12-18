#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int msg; } ;
struct TYPE_25__ {int /*<<< orphan*/  fc_tx; int /*<<< orphan*/  fc_rx; int /*<<< orphan*/  autoneg; } ;
struct TYPE_23__ {size_t sqs_id; scalar_t__ nicvf; } ;
struct TYPE_22__ {int /*<<< orphan*/  qs_count; } ;
struct TYPE_21__ {int link_up; int /*<<< orphan*/  mac_type; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;
struct TYPE_20__ {int /*<<< orphan*/  ind_tbl_size; } ;
struct TYPE_18__ {int vf_id; int tns_mode; int /*<<< orphan*/  loopback_supported; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  node_id; } ;
union nic_mbx {TYPE_9__ msg; TYPE_8__ pfc; TYPE_6__ nicvf; TYPE_5__ sqs_alloc; TYPE_4__ link_status; int /*<<< orphan*/  bgx_stats; TYPE_3__ rss_size; TYPE_1__ nic_cfg; } ;
typedef  int u64 ;
struct TYPE_24__ {int /*<<< orphan*/  fc_tx; int /*<<< orphan*/  fc_rx; int /*<<< orphan*/  autoneg; } ;
struct TYPE_19__ {int /*<<< orphan*/  rss_size; } ;
struct nicvf {int pf_acked; int vf_id; int tns_mode; int link_up; int pf_nacked; TYPE_10__* netdev; TYPE_7__ pfc; struct nicvf* pnicvf; struct nicvf** snicvf; int /*<<< orphan*/  sqs_count; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  mac_type; TYPE_2__ rss_info; int /*<<< orphan*/  loopback_supported; int /*<<< orphan*/  sqs_mode; int /*<<< orphan*/  set_mac_pending; int /*<<< orphan*/  node; } ;
struct TYPE_17__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
#define  NIC_MBOX_MSG_ACK 137 
#define  NIC_MBOX_MSG_ALLOC_SQS 136 
#define  NIC_MBOX_MSG_BGX_LINK_CHANGE 135 
#define  NIC_MBOX_MSG_BGX_STATS 134 
#define  NIC_MBOX_MSG_NACK 133 
#define  NIC_MBOX_MSG_PFC 132 
#define  NIC_MBOX_MSG_PNICVF_PTR 131 
#define  NIC_MBOX_MSG_READY 130 
#define  NIC_MBOX_MSG_RSS_SIZE 129 
#define  NIC_MBOX_MSG_SNICVF_PTR 128 
 int NIC_PF_VF_MAILBOX_SIZE ; 
 int NIC_VF_PF_MAILBOX_0_1 ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_10__*,char*,int) ; 
 int /*<<< orphan*/  netdev_err (TYPE_10__*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (TYPE_10__*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (TYPE_10__*) ; 
 int /*<<< orphan*/  netif_carrier_on (TYPE_10__*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (TYPE_10__*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (TYPE_10__*) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_read_bgx_stats (struct nicvf*,int /*<<< orphan*/ *) ; 
 int nicvf_reg_read (struct nicvf*,int) ; 

__attribute__((used)) static void  nicvf_handle_mbx_intr(struct nicvf *nic)
{
	union nic_mbx mbx = {};
	u64 *mbx_data;
	u64 mbx_addr;
	int i;

	mbx_addr = NIC_VF_PF_MAILBOX_0_1;
	mbx_data = (u64 *)&mbx;

	for (i = 0; i < NIC_PF_VF_MAILBOX_SIZE; i++) {
		*mbx_data = nicvf_reg_read(nic, mbx_addr);
		mbx_data++;
		mbx_addr += sizeof(u64);
	}

	netdev_dbg(nic->netdev, "Mbox message: msg: 0x%x\n", mbx.msg.msg);
	switch (mbx.msg.msg) {
	case NIC_MBOX_MSG_READY:
		nic->pf_acked = true;
		nic->vf_id = mbx.nic_cfg.vf_id & 0x7F;
		nic->tns_mode = mbx.nic_cfg.tns_mode & 0x7F;
		nic->node = mbx.nic_cfg.node_id;
		if (!nic->set_mac_pending)
			ether_addr_copy(nic->netdev->dev_addr,
					mbx.nic_cfg.mac_addr);
		nic->sqs_mode = mbx.nic_cfg.sqs_mode;
		nic->loopback_supported = mbx.nic_cfg.loopback_supported;
		nic->link_up = false;
		nic->duplex = 0;
		nic->speed = 0;
		break;
	case NIC_MBOX_MSG_ACK:
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_NACK:
		nic->pf_nacked = true;
		break;
	case NIC_MBOX_MSG_RSS_SIZE:
		nic->rss_info.rss_size = mbx.rss_size.ind_tbl_size;
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_BGX_STATS:
		nicvf_read_bgx_stats(nic, &mbx.bgx_stats);
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_BGX_LINK_CHANGE:
		nic->pf_acked = true;
		if (nic->link_up != mbx.link_status.link_up) {
			nic->link_up = mbx.link_status.link_up;
			nic->duplex = mbx.link_status.duplex;
			nic->speed = mbx.link_status.speed;
			nic->mac_type = mbx.link_status.mac_type;
			if (nic->link_up) {
				netdev_info(nic->netdev,
					    "Link is Up %d Mbps %s duplex\n",
					    nic->speed,
					    nic->duplex == DUPLEX_FULL ?
					    "Full" : "Half");
				netif_carrier_on(nic->netdev);
				netif_tx_start_all_queues(nic->netdev);
			} else {
				netdev_info(nic->netdev, "Link is Down\n");
				netif_carrier_off(nic->netdev);
				netif_tx_stop_all_queues(nic->netdev);
			}
		}
		break;
	case NIC_MBOX_MSG_ALLOC_SQS:
		nic->sqs_count = mbx.sqs_alloc.qs_count;
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_SNICVF_PTR:
		/* Primary VF: make note of secondary VF's pointer
		 * to be used while packet transmission.
		 */
		nic->snicvf[mbx.nicvf.sqs_id] =
			(struct nicvf *)mbx.nicvf.nicvf;
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_PNICVF_PTR:
		/* Secondary VF/Qset: make note of primary VF's pointer
		 * to be used while packet reception, to handover packet
		 * to primary VF's netdev.
		 */
		nic->pnicvf = (struct nicvf *)mbx.nicvf.nicvf;
		nic->pf_acked = true;
		break;
	case NIC_MBOX_MSG_PFC:
		nic->pfc.autoneg = mbx.pfc.autoneg;
		nic->pfc.fc_rx = mbx.pfc.fc_rx;
		nic->pfc.fc_tx = mbx.pfc.fc_tx;
		nic->pf_acked = true;
		break;
	default:
		netdev_err(nic->netdev,
			   "Invalid message from PF, msg 0x%x\n", mbx.msg.msg);
		break;
	}
	nicvf_clear_intr(nic, NICVF_INTR_MBOX, 0);
}