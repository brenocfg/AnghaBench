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
typedef  int const u32 ;
struct sk_buff {int dummy; } ;
struct net_device_stats {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; } ;
struct net_device {struct net_device_stats stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_error; } ;
struct TYPE_4__ {TYPE_1__ can_stats; } ;
struct ifi_canfd_priv {scalar_t__ base; TYPE_2__ can; } ;
struct can_frame {int can_id; scalar_t__ can_dlc; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int CAN_ERR_BUSERROR ; 
 int CAN_ERR_PROT ; 
 int /*<<< orphan*/  CAN_ERR_PROT_BIT0 ; 
 int /*<<< orphan*/  CAN_ERR_PROT_BIT1 ; 
 int /*<<< orphan*/  CAN_ERR_PROT_FORM ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_ACK ; 
 int /*<<< orphan*/  CAN_ERR_PROT_LOC_CRC_SEQ ; 
 int /*<<< orphan*/  CAN_ERR_PROT_OVERLOAD ; 
 int /*<<< orphan*/  CAN_ERR_PROT_STUFF ; 
 scalar_t__ IFI_CANFD_ERROR_CTR ; 
 int const IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST ; 
 int const IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST ; 
 int const IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST ; 
 int const IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST ; 
 int /*<<< orphan*/  IFI_CANFD_ERROR_CTR_ER_ENABLE ; 
 int /*<<< orphan*/  IFI_CANFD_ERROR_CTR_ER_RESET ; 
 int const IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST ; 
 int const IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST ; 
 int const IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST ; 
 scalar_t__ IFI_CANFD_INTERRUPT ; 
 int /*<<< orphan*/  IFI_CANFD_INTERRUPT_ERROR_COUNTER ; 
 struct sk_buff* alloc_can_err_skb (struct net_device*,struct can_frame**) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ifi_canfd_handle_lec_err(struct net_device *ndev)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	struct net_device_stats *stats = &ndev->stats;
	struct can_frame *cf;
	struct sk_buff *skb;
	u32 errctr = readl(priv->base + IFI_CANFD_ERROR_CTR);
	const u32 errmask = IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST |
			    IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST |
			    IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST;

	if (!(errctr & errmask))	/* No error happened. */
		return 0;

	priv->can.can_stats.bus_error++;
	stats->rx_errors++;

	/* Propagate the error condition to the CAN stack. */
	skb = alloc_can_err_skb(ndev, &cf);
	if (unlikely(!skb))
		return 0;

	/* Read the error counter register and check for new errors. */
	cf->can_id |= CAN_ERR_PROT | CAN_ERR_BUSERROR;

	if (errctr & IFI_CANFD_ERROR_CTR_OVERLOAD_FIRST)
		cf->data[2] |= CAN_ERR_PROT_OVERLOAD;

	if (errctr & IFI_CANFD_ERROR_CTR_ACK_ERROR_FIRST)
		cf->data[3] = CAN_ERR_PROT_LOC_ACK;

	if (errctr & IFI_CANFD_ERROR_CTR_BIT0_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_BIT0;

	if (errctr & IFI_CANFD_ERROR_CTR_BIT1_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_BIT1;

	if (errctr & IFI_CANFD_ERROR_CTR_STUFF_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_STUFF;

	if (errctr & IFI_CANFD_ERROR_CTR_CRC_ERROR_FIRST)
		cf->data[3] = CAN_ERR_PROT_LOC_CRC_SEQ;

	if (errctr & IFI_CANFD_ERROR_CTR_FORM_ERROR_FIRST)
		cf->data[2] |= CAN_ERR_PROT_FORM;

	/* Reset the error counter, ack the IRQ and re-enable the counter. */
	writel(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	writel(IFI_CANFD_INTERRUPT_ERROR_COUNTER,
	       priv->base + IFI_CANFD_INTERRUPT);
	writel(IFI_CANFD_ERROR_CTR_ER_ENABLE, priv->base + IFI_CANFD_ERROR_CTR);

	stats->rx_packets++;
	stats->rx_bytes += cf->can_dlc;
	netif_receive_skb(skb);

	return 1;
}