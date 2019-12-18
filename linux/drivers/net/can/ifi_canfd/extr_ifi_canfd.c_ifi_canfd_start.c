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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct ifi_canfd_priv {scalar_t__ base; TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_FD ; 
 int CAN_CTRLMODE_FD_NON_ISO ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 scalar_t__ IFI_CANFD_ERROR_CTR ; 
 int IFI_CANFD_ERROR_CTR_ER_ENABLE ; 
 int IFI_CANFD_ERROR_CTR_ER_RESET ; 
 int IFI_CANFD_ERROR_CTR_UNLOCK_MAGIC ; 
 scalar_t__ IFI_CANFD_INTERRUPT ; 
 scalar_t__ IFI_CANFD_INTERRUPT_SET_IRQ ; 
 scalar_t__ IFI_CANFD_REPEAT ; 
 scalar_t__ IFI_CANFD_RXSTCMD ; 
 int IFI_CANFD_RXSTCMD_RESET ; 
 scalar_t__ IFI_CANFD_STCMD ; 
 int IFI_CANFD_STCMD_BUSMONITOR ; 
 int IFI_CANFD_STCMD_DISABLE_CANFD ; 
 int IFI_CANFD_STCMD_ENABLE ; 
 int IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING ; 
 int IFI_CANFD_STCMD_ENABLE_ISO ; 
 int IFI_CANFD_STCMD_HARDRESET ; 
 int IFI_CANFD_STCMD_LOOPBACK ; 
 int IFI_CANFD_STCMD_NORMAL_MODE ; 
 scalar_t__ IFI_CANFD_SUSPEND ; 
 scalar_t__ IFI_CANFD_TXSTCMD ; 
 int IFI_CANFD_TXSTCMD_RESET ; 
 int /*<<< orphan*/  ifi_canfd_irq_enable (struct net_device*,int) ; 
 int /*<<< orphan*/  ifi_canfd_set_bittiming (struct net_device*) ; 
 int /*<<< orphan*/  ifi_canfd_set_filters (struct net_device*) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ifi_canfd_start(struct net_device *ndev)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	u32 stcmd;

	/* Reset the IP */
	writel(IFI_CANFD_STCMD_HARDRESET, priv->base + IFI_CANFD_STCMD);
	writel(IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING,
	       priv->base + IFI_CANFD_STCMD);

	ifi_canfd_set_bittiming(ndev);
	ifi_canfd_set_filters(ndev);

	/* Reset FIFOs */
	writel(IFI_CANFD_RXSTCMD_RESET, priv->base + IFI_CANFD_RXSTCMD);
	writel(0, priv->base + IFI_CANFD_RXSTCMD);
	writel(IFI_CANFD_TXSTCMD_RESET, priv->base + IFI_CANFD_TXSTCMD);
	writel(0, priv->base + IFI_CANFD_TXSTCMD);

	/* Repeat transmission until successful */
	writel(0, priv->base + IFI_CANFD_REPEAT);
	writel(0, priv->base + IFI_CANFD_SUSPEND);

	/* Clear all pending interrupts */
	writel((u32)(~IFI_CANFD_INTERRUPT_SET_IRQ),
	       priv->base + IFI_CANFD_INTERRUPT);

	stcmd = IFI_CANFD_STCMD_ENABLE | IFI_CANFD_STCMD_NORMAL_MODE |
		IFI_CANFD_STCMD_ENABLE_7_9_8_8_TIMING;

	if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		stcmd |= IFI_CANFD_STCMD_BUSMONITOR;

	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		stcmd |= IFI_CANFD_STCMD_LOOPBACK;

	if ((priv->can.ctrlmode & CAN_CTRLMODE_FD) &&
	    !(priv->can.ctrlmode & CAN_CTRLMODE_FD_NON_ISO))
		stcmd |= IFI_CANFD_STCMD_ENABLE_ISO;

	if (!(priv->can.ctrlmode & CAN_CTRLMODE_FD))
		stcmd |= IFI_CANFD_STCMD_DISABLE_CANFD;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;

	ifi_canfd_irq_enable(ndev, 1);

	/* Unlock, reset and enable the error counter. */
	writel(IFI_CANFD_ERROR_CTR_UNLOCK_MAGIC,
	       priv->base + IFI_CANFD_ERROR_CTR);
	writel(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	writel(IFI_CANFD_ERROR_CTR_ER_ENABLE, priv->base + IFI_CANFD_ERROR_CTR);

	/* Enable controller */
	writel(stcmd, priv->base + IFI_CANFD_STCMD);
}