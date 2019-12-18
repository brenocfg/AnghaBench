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
struct net_device {int dummy; } ;
struct TYPE_2__ {int ctrlmode_supported; int /*<<< orphan*/  do_get_berr_counter; int /*<<< orphan*/  do_set_mode; int /*<<< orphan*/ * bittiming_const; } ;
struct c_can_priv {TYPE_1__ can; struct net_device* dev; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int CAN_CTRLMODE_BERR_REPORTING ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  C_CAN_MSG_OBJ_TX_NUM ; 
 int /*<<< orphan*/  C_CAN_NAPI_WEIGHT ; 
 struct net_device* alloc_candev (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_can_bittiming_const ; 
 int /*<<< orphan*/  c_can_get_berr_counter ; 
 int /*<<< orphan*/  c_can_poll ; 
 int /*<<< orphan*/  c_can_set_mode ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_napi_add (struct net_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct net_device *alloc_c_can_dev(void)
{
	struct net_device *dev;
	struct c_can_priv *priv;

	dev = alloc_candev(sizeof(struct c_can_priv), C_CAN_MSG_OBJ_TX_NUM);
	if (!dev)
		return NULL;

	priv = netdev_priv(dev);
	netif_napi_add(dev, &priv->napi, c_can_poll, C_CAN_NAPI_WEIGHT);

	priv->dev = dev;
	priv->can.bittiming_const = &c_can_bittiming_const;
	priv->can.do_set_mode = c_can_set_mode;
	priv->can.do_get_berr_counter = c_can_get_berr_counter;
	priv->can.ctrlmode_supported = CAN_CTRLMODE_LOOPBACK |
					CAN_CTRLMODE_LISTENONLY |
					CAN_CTRLMODE_BERR_REPORTING;

	return dev;
}