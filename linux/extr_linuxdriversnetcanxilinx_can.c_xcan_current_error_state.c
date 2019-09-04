#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;} ;
struct net_device {int dummy; } ;
typedef  enum can_state { ____Placeholder_can_state } can_state ;

/* Variables and functions */
 int CAN_STATE_ERROR_ACTIVE ; 
 int CAN_STATE_ERROR_PASSIVE ; 
 int CAN_STATE_ERROR_WARNING ; 
 int XCAN_SR_ERRWRN_MASK ; 
 int XCAN_SR_ESTAT_MASK ; 
 int /*<<< orphan*/  XCAN_SR_OFFSET ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum can_state xcan_current_error_state(struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	u32 status = priv->read_reg(priv, XCAN_SR_OFFSET);

	if ((status & XCAN_SR_ESTAT_MASK) == XCAN_SR_ESTAT_MASK)
		return CAN_STATE_ERROR_PASSIVE;
	else if (status & XCAN_SR_ERRWRN_MASK)
		return CAN_STATE_ERROR_WARNING;
	else
		return CAN_STATE_ERROR_ACTIVE;
}