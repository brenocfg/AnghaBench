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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct xcan_priv {TYPE_1__ can; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int /*<<< orphan*/  CAN_STATE_SLEEPING ; 
 int XCAN_IXR_SLP_MASK ; 
 int XCAN_IXR_WKUP_MASK ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void xcan_state_interrupt(struct net_device *ndev, u32 isr)
{
	struct xcan_priv *priv = netdev_priv(ndev);

	/* Check for Sleep interrupt if set put CAN device in sleep state */
	if (isr & XCAN_IXR_SLP_MASK)
		priv->can.state = CAN_STATE_SLEEPING;

	/* Check for Wake up interrupt if set put CAN device in Active state */
	if (isr & XCAN_IXR_WKUP_MASK)
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
}