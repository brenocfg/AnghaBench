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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct pch_can_priv {TYPE_2__* regs; TYPE_3__* ndev; } ;
struct net_device_stats {int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int dummy; } ;
struct can_frame {int can_id; int can_dlc; int* data; } ;
typedef  int id2 ;
typedef  int canid_t ;
struct TYPE_6__ {struct net_device_stats stats; } ;
struct TYPE_5__ {TYPE_1__* ifregs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  mcont; int /*<<< orphan*/  id1; int /*<<< orphan*/  id2; int /*<<< orphan*/  creq; int /*<<< orphan*/  cmask; } ;

/* Variables and functions */
 int CAN_EFF_FLAG ; 
 int CAN_RTR_FLAG ; 
 int CAN_SFF_MASK ; 
 int /*<<< orphan*/  PCH_CMASK_RX_TX_GET ; 
 int PCH_ID2_DIR ; 
 int PCH_ID2_XTD ; 
 int PCH_IF_MCONT_EOB ; 
 int PCH_IF_MCONT_MSGLOST ; 
 int PCH_IF_MCONT_NEWDAT ; 
 struct sk_buff* alloc_can_skb (TYPE_3__*,struct can_frame**) ; 
 int get_can_dlc (int) ; 
 int ioread16 (int /*<<< orphan*/ *) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  pch_can_rw_msg_obj (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pch_can_rx_msg_lost (struct net_device*,int) ; 
 int /*<<< orphan*/  pch_fifo_thresh (struct pch_can_priv*,int) ; 

__attribute__((used)) static int pch_can_rx_normal(struct net_device *ndev, u32 obj_num, int quota)
{
	u32 reg;
	canid_t id;
	int rcv_pkts = 0;
	struct sk_buff *skb;
	struct can_frame *cf;
	struct pch_can_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &(priv->ndev->stats);
	int i;
	u32 id2;
	u16 data_reg;

	do {
		/* Reading the message object from the Message RAM */
		iowrite32(PCH_CMASK_RX_TX_GET, &priv->regs->ifregs[0].cmask);
		pch_can_rw_msg_obj(&priv->regs->ifregs[0].creq, obj_num);

		/* Reading the MCONT register. */
		reg = ioread32(&priv->regs->ifregs[0].mcont);

		if (reg & PCH_IF_MCONT_EOB)
			break;

		/* If MsgLost bit set. */
		if (reg & PCH_IF_MCONT_MSGLOST) {
			pch_can_rx_msg_lost(ndev, obj_num);
			rcv_pkts++;
			quota--;
			obj_num++;
			continue;
		} else if (!(reg & PCH_IF_MCONT_NEWDAT)) {
			obj_num++;
			continue;
		}

		skb = alloc_can_skb(priv->ndev, &cf);
		if (!skb) {
			netdev_err(ndev, "alloc_can_skb Failed\n");
			return rcv_pkts;
		}

		/* Get Received data */
		id2 = ioread32(&priv->regs->ifregs[0].id2);
		if (id2 & PCH_ID2_XTD) {
			id = (ioread32(&priv->regs->ifregs[0].id1) & 0xffff);
			id |= (((id2) & 0x1fff) << 16);
			cf->can_id = id | CAN_EFF_FLAG;
		} else {
			id = (id2 >> 2) & CAN_SFF_MASK;
			cf->can_id = id;
		}

		if (id2 & PCH_ID2_DIR)
			cf->can_id |= CAN_RTR_FLAG;

		cf->can_dlc = get_can_dlc((ioread32(&priv->regs->
						    ifregs[0].mcont)) & 0xF);

		for (i = 0; i < cf->can_dlc; i += 2) {
			data_reg = ioread16(&priv->regs->ifregs[0].data[i / 2]);
			cf->data[i] = data_reg;
			cf->data[i + 1] = data_reg >> 8;
		}

		netif_receive_skb(skb);
		rcv_pkts++;
		stats->rx_packets++;
		quota--;
		stats->rx_bytes += cf->can_dlc;

		pch_fifo_thresh(priv, obj_num);
		obj_num++;
	} while (quota > 0);

	return rcv_pkts;
}