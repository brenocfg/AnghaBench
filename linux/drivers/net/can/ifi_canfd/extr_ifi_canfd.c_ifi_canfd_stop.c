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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct ifi_canfd_priv {TYPE_1__ can; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 scalar_t__ IFI_CANFD_ERROR_CTR ; 
 int /*<<< orphan*/  IFI_CANFD_ERROR_CTR_ER_RESET ; 
 scalar_t__ IFI_CANFD_INTERRUPT ; 
 scalar_t__ IFI_CANFD_INTERRUPT_SET_IRQ ; 
 scalar_t__ IFI_CANFD_IRQMASK ; 
 scalar_t__ IFI_CANFD_STCMD ; 
 int /*<<< orphan*/  IFI_CANFD_STCMD_HARDRESET ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ifi_canfd_stop(struct net_device *ndev)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);

	/* Reset and disable the error counter. */
	writel(IFI_CANFD_ERROR_CTR_ER_RESET, priv->base + IFI_CANFD_ERROR_CTR);
	writel(0, priv->base + IFI_CANFD_ERROR_CTR);

	/* Reset the IP */
	writel(IFI_CANFD_STCMD_HARDRESET, priv->base + IFI_CANFD_STCMD);

	/* Mask all interrupts */
	writel(~0, priv->base + IFI_CANFD_IRQMASK);

	/* Clear all pending interrupts */
	writel((u32)(~IFI_CANFD_INTERRUPT_SET_IRQ),
	       priv->base + IFI_CANFD_INTERRUPT);

	/* Set the state as STOPPED */
	priv->can.state = CAN_STATE_STOPPED;
}