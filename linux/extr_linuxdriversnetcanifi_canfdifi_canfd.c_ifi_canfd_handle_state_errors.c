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
struct TYPE_2__ {scalar_t__ state; } ;
struct ifi_canfd_priv {TYPE_1__ can; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ CAN_STATE_BUS_OFF ; 
 scalar_t__ CAN_STATE_ERROR_ACTIVE ; 
 scalar_t__ CAN_STATE_ERROR_PASSIVE ; 
 scalar_t__ CAN_STATE_ERROR_WARNING ; 
 scalar_t__ IFI_CANFD_STCMD ; 
 int IFI_CANFD_STCMD_BUSOFF ; 
 int IFI_CANFD_STCMD_ERROR_ACTIVE ; 
 int IFI_CANFD_STCMD_ERROR_PASSIVE ; 
 int IFI_CANFD_STCMD_ERROR_WARNING ; 
 scalar_t__ ifi_canfd_handle_state_change (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 struct ifi_canfd_priv* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int ifi_canfd_handle_state_errors(struct net_device *ndev)
{
	struct ifi_canfd_priv *priv = netdev_priv(ndev);
	u32 stcmd = readl(priv->base + IFI_CANFD_STCMD);
	int work_done = 0;

	if ((stcmd & IFI_CANFD_STCMD_ERROR_ACTIVE) &&
	    (priv->can.state != CAN_STATE_ERROR_ACTIVE)) {
		netdev_dbg(ndev, "Error, entered active state\n");
		work_done += ifi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_ACTIVE);
	}

	if ((stcmd & IFI_CANFD_STCMD_ERROR_WARNING) &&
	    (priv->can.state != CAN_STATE_ERROR_WARNING)) {
		netdev_dbg(ndev, "Error, entered warning state\n");
		work_done += ifi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_WARNING);
	}

	if ((stcmd & IFI_CANFD_STCMD_ERROR_PASSIVE) &&
	    (priv->can.state != CAN_STATE_ERROR_PASSIVE)) {
		netdev_dbg(ndev, "Error, entered passive state\n");
		work_done += ifi_canfd_handle_state_change(ndev,
						CAN_STATE_ERROR_PASSIVE);
	}

	if ((stcmd & IFI_CANFD_STCMD_BUSOFF) &&
	    (priv->can.state != CAN_STATE_BUS_OFF)) {
		netdev_dbg(ndev, "Error, entered bus-off state\n");
		work_done += ifi_canfd_handle_state_change(ndev,
						CAN_STATE_BUS_OFF);
	}

	return work_done;
}