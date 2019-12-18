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
struct TYPE_2__ {int ctrlmode; } ;
struct ifi_canfd_priv {scalar_t__ base; TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int IFI_CANFD_INTERRUPT_ERROR_COUNTER ; 
 scalar_t__ IFI_CANFD_IRQMASK ; 
 int IFI_CANFD_IRQMASK_ERROR_BUSOFF ; 
 int IFI_CANFD_IRQMASK_ERROR_STATE_CHG ; 
 int IFI_CANFD_IRQMASK_ERROR_WARNING ; 
 int IFI_CANFD_IRQMASK_RXFIFO_NEMPTY ; 
 int IFI_CANFD_IRQMASK_SET_ERR ; 
 int IFI_CANFD_IRQMASK_SET_RX ; 
 int IFI_CANFD_IRQMASK_SET_TS ; 
 int IFI_CANFD_IRQMASK_SET_TX ; 
 int IFI_CANFD_IRQMASK_TXFIFO_EMPTY ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void ifi_canfd_irq_enable(struct net_device *ndev, bool enable)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	u32 enirq = 0;

	if (enable) {
		enirq = IFI_CANFD_IRQMASK_TXFIFO_EMPTY |
			IFI_CANFD_IRQMASK_RXFIFO_NEMPTY |
			IFI_CANFD_IRQMASK_ERROR_STATE_CHG |
			IFI_CANFD_IRQMASK_ERROR_WARNING |
			IFI_CANFD_IRQMASK_ERROR_BUSOFF;
		if (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
			enirq |= IFI_CANFD_INTERRUPT_ERROR_COUNTER;
	}

	writel(IFI_CANFD_IRQMASK_SET_ERR |
	       IFI_CANFD_IRQMASK_SET_TS |
	       IFI_CANFD_IRQMASK_SET_TX |
	       IFI_CANFD_IRQMASK_SET_RX | enirq,
	       priv->base + IFI_CANFD_IRQMASK);
}